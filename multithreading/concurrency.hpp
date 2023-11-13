#include <iostream>
#include <future>
#include <numeric>
#include <queue>
#include <sstream>
#include <vector>
#include <map>
/// mutex

/// std::lock_gaurd

std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

void testLockGaurd()
{
    auto save_page = [](const std::string& url)
    {
        // simulate a long page fetch
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::string result = "fake content";

        std::lock_guard<std::mutex> guard(g_pages_mutex);
        g_pages[url] = result;
    };

    std::thread t1(save_page, "http://foo");
    std::thread t2(save_page, "http://bar");
    t1.join();
    t2.join();

    // safe to access g_pages without lock now, as the threads are joined
    for (const auto& pair : g_pages)
    {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}

/// std::recursive_gaurd

/// std::try_lock -> m.try_lock() -> std::lock_gaurd(m, std::adopt_lock)
/*
while (m.try_lock() == false) {
    doSomeOtherStuff();
}
std::lock_guard<std::mutex> lb(m, std::adopt_lock);

------------------------------------------------------------------

std::timed_mutex m;

//try for 1sec to acquire a lock
if (m.try_lock_for(std::chrono::seconds(1))) {
    std::lock_guard<std::timed_mutex> lg(m, std::adopt_lock);
    ...
} else {
    couldNotGetTheLock();
}
*/

/// std::unique_lock
///
int counter = 0;
std::mutex counter_mutex;
std::vector<std::thread> threads;
void testUniqueLock()
{
    auto worker_task = [&](int id)
    {
        std::unique_lock<std::mutex> lock(counter_mutex);
        ++counter;
        std::cout << id << ", initial counter: " << counter << '\n';
        lock.unlock();

        // don't hold the lock while we simulate an expensive operation
        std::this_thread::sleep_for(std::chrono::seconds(1));

        lock.lock();
        ++counter;
        std::cout << id << ", final counter: " << counter << '\n';
    };

    for (int i = 0; i < 10; ++i)
        threads.emplace_back(worker_task, i);

    for (auto& thread : threads)
        thread.join();
}

////////////////////////////////////////Conditional Variable/////////////////////////////////////////////////////////
/*
Sometimes, tasks performed by different threads have to wait for each other. Thus, we have to synchronize concurrent
operations for other reasons than to access the same data.

Condition variables can be used to synchronize logical dependencies in data flow bt threads. A condition variable is a
variable by which a thread can wake up one or multi other waiting threads.
*/
bool readyFlag;                       // a flag signaling the cond is indeed satisfied
std::mutex readyMutex;                // a mutex
std::condition_variable readyCondVar; // a cond var

void testConditionalVariable()
{
    auto thread1 = []()
    {
        std::cout << "return\n";
        std::cin.get();
        {
            std::scoped_lock<std::mutex> sl(readyMutex);
            readyFlag = true;
        } // realease lock
        readyCondVar.notify_one();
    };

    auto thread2 = []()
    {
        {
            std::unique_lock<std::mutex> ul(readyMutex);
            readyCondVar.wait(ul, []() { return readyFlag; });
        }
        std::cout << "done" << std::endl;
    };

    auto f1 = std::async(std::launch::async, thread1);
    auto f2 = std::async(std::launch::async, thread2);
}

/// example of a multi-thread queue
///

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCond;

void testMultithreadQueue()
{
    auto provider = [](int value)
    {
        // push different vals
        for (int i = 0; i < 6; ++i)
        {
            {
                std::lock_guard<std::mutex> lg(queueMutex);
                queue.push(value + i);
            } // release lock
            std::cout << "provide: " << value + i << "\n";

            queueCond.notify_one();

            std::this_thread::sleep_for(std::chrono::milliseconds(value));
        }
    };

    auto consumer = [](int num)
    {
        while (true)
        {
            int val;
            {
                std::unique_lock<std::mutex> ul(queueMutex);
                queueCond.wait(ul, [] { return !queue.empty(); });
                val = queue.front();
                queue.pop();
            } // release lock
            std::cout << "consumer " << num << ": " << val << std::endl;
        }
    };

    // start three providers for values 100+, 300+, 500+
    auto p1 = std::async(std::launch::async, provider, 100);
    auto p2 = std::async(std::launch::async, provider, 300);
    auto p3 = std::async(std::launch::async, provider, 500);

    // start two consumers printing the vals
    auto c1 = std::async(std::launch::async, consumer, 1);
    auto c2 = std::async(std::launch::async, consumer, 2);
}

////////////////////////////////////////Atomic Variable/////////////////////////////////////////////////////////
// bool readyFlag;
std::mutex readyFlagMutex;

void thread1()
{
    // do something thread2 needs as preparation
    std::lock_guard<std::mutex> lg(readyFlagMutex);
    readyFlag = true;
}

void thread2()
{
    // wait until readyFlag is true (thread1 is done)
    {
        std::unique_lock<std::mutex> ul(readyFlagMutex);
        while (!readyFlag)
        {
            ul.unlock();
            std::this_thread::yield(); // hint to reschedule to the next thread
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ul.lock();
        }
    } // release lock

    // do whatever shall happen after thread1 has prepared things
}

//-------------- YOU CAN MAKE IT LIKE BELOW --------------

// std::atomic<bool> readyFlag(false);

// void thread1()
//{
//     // do something thread2 needs as preparation ...
//     readyFlag.store(true);
// }

// void thread2()
//{
//     // wait until readyFlag is true (thread1 is done)
//     while (!readyFlag.load())
//     {
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     }

//    // do whatever shall happen after thread1 has prepared things
//}
