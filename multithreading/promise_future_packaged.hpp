#include <iostream>
#include <future>
#include <numeric>
#include <sstream>
#include <vector>

////////////////////////////////////////////Promise Test//////////////////////////////////////////////////////////////
/// \brief testPromise1
///
void testPromise1()
{
    std::promise<int> p;
    std::future<int> f = p.get_future();
    p.set_value(45);
    std::cout << f.get() << "\n";
}

/// Strictly speaking, calling std::future<T>::get() or std::promise<T>::set_value() multiple times is an Undefined
/// Behavior. However, the C++ standard encourages C++ authors to throw in std::future_error as an exception.
void testPromise2()
{
    std::promise<int> p;
    auto f = p.get_future();
    std::thread t([](auto p) { p.set_value(45); }, std::move(p));
    std::cout << f.get() << "\n";
    t.join();
}

void testPromise3()
{
    std::promise<int> p;
    auto f = p.get_future();

    std::thread t(
        [](auto p)
        {
            p.set_value(45);
            try
            {
                p.set_value(46);
            }
            catch (std::future_error& e)
            {
                std::cerr << "caught " << e.what() << "\n";
            }
        },
        std::move(p));

    std::cout << f.get() << "\n";

    try
    {
        std::cout << f.get() << "\n";
    }
    catch (std::future_error& e)
    {
        std::cerr << "caught " << e.what() << "\n";
    }

    t.join();
}

void testPromise4()
{
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t(
        [](std::promise<int> p)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            p.set_value(42);
        },
        std::move(p));

    for (int i = 0;; ++i)
    {
        std::cout << "waiting attempt " << i << " ..." << std::endl;
        std::future_status status = f.wait_for(std::chrono::seconds(1));
        if (status != std::future_status::timeout)
        {
            break;
        }
    }
    std::cout << f.get() << std::endl;

    t.join();
}

void testPromise5()
{
    std::promise<int> p;
    auto f = p.get_future();
    auto acc = [](std::vector<int>::iterator begin, std::vector<int>::iterator end, std::promise<int> accPromise)
    {
        int sum = std::accumulate(begin, end, 0);
        accPromise.set_value(sum);
    };
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

    std::thread t(acc, numbers.begin(), numbers.end(), std::move(p));
    f.wait();
    std::cout << f.get() << "\n";
    t.join();
}

/// use condition variables, which the detached threads use to signal that they have finished. Before leaving main() or
/// calling exit(), you'd have to set these condition variables then to signal that a destruction is psbl;
///
void testDetachJoin()
{
    auto doSomething = [](int num, char c)
    {
        // any uncaught exception would cause the prog to terminate
        try
        {
            std::cout << num << " saman\n";
        }
        // make sure no exception leaves the thread and terminates the program
        catch (const std::exception& e)
        {
            std::cerr << "thread-exception (thread " << std::this_thread::get_id() << "): " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "thread-exception (thread " << std::this_thread::get_id() << ")" << std::endl;
        }
    };

    try
    {
        std::thread t1(doSomething, 5, '.'); // print 5 dots in separate thread
        std::cout << "- started fg thread " << t1.get_id() << std::endl;

        // print other chars in other bg threads
        for (int i = 0; i < 5; ++i)
        {
            std::thread t(doSomething, 10, 'a' + i); // print 10 chars in separate thread
            std::cout << "- detach started bg thread " << t.get_id() << std::endl;
            t.detach(); // detach thread into the bg
        }

        //        std::cin.get(); // wait for any input (return)
        std::cout << "- join fg thread " << t1.get_id() << std::endl;
        t1.join(); // wait for t1 to finish
    }
    catch (const std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}
////////////////////////////////////////////Async Test//////////////////////////////////////////////////////////////

/// \brief testAsync
///
void testAsync()
{
    auto future = std::async(
        std::launch::async,
        []()
        {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            return 8;
        });

    std::cout << "wainting.... \n";
    std::future_status status;
    do
    {
        status = future.wait_for(std::chrono::seconds(1));
        if (status == std::future_status::deferred)
        {
            std::cout << "deferred\n";
        }
        else if (status == std::future_status::timeout)
        {
            std::cout << "timeout\n";
        }
        else if (status == std::future_status::ready)
        {
            std::cout << "ready!\n";
        }
    } while (status != std::future_status::ready);
    std::cout << "result is " << future.get() << '\n';
}

void testAsyncLaucnhPolicy()
{
    auto print_ten = [](char c, int ms)
    {
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            std::cout << c;
        }
    };

    std::cout << "with launch::async: ";
    std::future<void> foo = std::async(std::launch::async, print_ten, '*', 100);
    std::future<void> bar = std::async(std::launch::async, print_ten, '@', 200);
    // async "get" (wait for foo and bar to be ready):
    foo.get();
    bar.get();
    std::cout << "\n\n";

    std::cout << "with launch::deferred: ";
    foo = std::async(std::launch::deferred, print_ten, '*', 100);
    bar = std::async(std::launch::deferred, print_ten, '@', 200);
    // deferred "get" (perform the actual calls):
    foo.get();
    bar.get();
    std::cout << '\n';
    /*
        possible output:
        with launch::async: **@**@**@*@**@*@@@@@
        with launch::deferred: **********@@@@@@@@@@
     */
}
////////////////////////////////////////////Exception Thread Test/////////////////////////////////////////////////////////////

///
/// \brief exceptionHandlingThread1
///
void exceptionHandlingThread1()
{
    std::promise<int> p;
    auto f = p.get_future();

    /// It is worth noting that p.set_exception(...) has the argument type std::exception_ptr, so we cannot pass the
    /// std::runtime_error object instance directly. We must first throw the exception with a throw statement, then get
    /// std::exception_ptr with std::current_exception() in the catch clause and call set_exception to send the exception.

    std::thread t(
        [](auto p)
        {
            try
            {
                throw std::runtime_error("some exception");
            }
            catch (...)
            {
                std::cout << "here\n";
                p.set_exception(std::current_exception());
            }
        },
        std::move(p));

    try
    {
        std::cout << f.get() << "\n";
    }
    catch (std::runtime_error& exp)
    {
        std::cout << "main thread: caught: " << exp.what() << "\n";
    }

    t.join();
}

////////////////////////////////////////////Future Test//////////////////////////////////////////////////////////////

/// Problem with shared future and further the solution

void futureProblem()
{
    std::promise<std::unique_ptr<int>> p;
    std::future<std::unique_ptr<int>> f = p.get_future();

    std::thread t1(
        [&f]()
        {
            std::cout << "t1: waiting\n" << std::flush;
            int value = *f.get(); // Race condition

            std::ostringstream ss;
            ss << "t1: " << value << "\n";
            std::cout << ss.str() << std::flush;
        });

    std::thread t2(
        [&f]()
        {
            std::cout << "t2: waiting\n" << std::flush;
            int value = *f.get(); // Race condition

            std::ostringstream ss;
            ss << "t2: " << value << "\n";
            std::cout << ss.str() << std::flush;
        });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    p.set_value(std::make_unique<int>(42));

    t1.join();
    t2.join();
}

void solveFutureProblem()
{
    std::promise<std::unique_ptr<int>> p;
    std::future<std::unique_ptr<int>> f = p.get_future();
    std::shared_future<std::unique_ptr<int>> sf = f.share(); // Added

    std::thread t1([sf]() { // Copy sf by value
        std::cout << "t1: waiting\n" << std::flush;
        int value = *sf.get();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::ostringstream ss;
        ss << "t1: " << value << "\n";
        std::cout << ss.str() << std::flush;
    });
    std::thread t2([sf]() { // Copy sf by value
        std::cout << "t2: waiting\n" << std::flush;
        int value = *sf.get();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::ostringstream ss;
        ss << "t2: " << value << "\n";
        std::cout << ss.str() << std::flush;
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    p.set_value(std::make_unique<int>(42));

    std::cout << "start\n";
    t1.join();
    std::cout << "between\n";
    t2.join();
    std::cout << "end\n";
}

////////////////////////////////////////////Packaged_Task Test//////////////////////////////////////////////////////////////

/// he std::packed_task class template is also defined in the <future> header file. Its purpose is to act as an adapter
/// between a ‘function’ or ‘function object’ and std::thread

void testPackagedTask()
{
    auto compute = [](int a, int b) { return 42 + a + b; };
    std::packaged_task<int(int, int)> task(compute);
    std::future<int> f = task.get_future();
    task(3, 4);
    std::cout << f.get() << std::endl;
}
