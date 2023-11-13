#ifndef FUTURES_HPP
#define FUTURES_HPP
#include <iostream>
#include <future>
#include <mutex>

/// Specify std::launch::async if asynchronicity is essential.
///

/*

    • The std::launch::async launch policy means that f must be run asynchro‐
    nously, i.e., on a different thread.

    • The std::launch::deferred launch policy means that f may run only when
    get or wait is called on the future returned by std::async.

 */

void f_future()
{
    using namespace std::chrono;
    std::this_thread::sleep_for(1s);
}

void test_futures()
{
    auto fut = std::async(f_future);
    using namespace std::chrono;
    if (fut.wait_for(0s) == std::future_status::deferred)
    {
        std::cout << "use wait or get on fut to call f_future sync";
    }
    while (fut.wait_for(100ms) != std::future_status::ready)
    {
        std::cout << "not ready!";
    }
}

template<typename F, typename... Ts>
inline std::future<typename std::result_of<F(Ts...)>>::type reallyAsync(F&& f, Ts&&... params)
{
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
}


void doWork(std::promise<int>&& prom)
{
    using namespace std::chrono;
    std::this_thread::sleep_for(2s);

    prom.set_value(42);
}



void testPromise()
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();


    std::thread t(doWork, std::move(promise));

    std::cout << "Waiting for the result....\n";

    int result = future.get();
    std::cout << "The result is " << result << "\n";

    t.join();
}
#endif // FUTURES_HPP
