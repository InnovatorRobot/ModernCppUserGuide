#ifndef SMART_PONITERS_H
#define SMART_PONITERS_H
#include <cassert>
#include <iostream>
#include <future>
#include <exception>
#include <functional>

//////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The MySharedPtr class
///
using uint = unsigned int;

template<class T>
class my_shared_ptr
{
private:
    T* ptr = nullptr;
    uint* refCount = nullptr;

public:
    my_shared_ptr() : ptr(nullptr), refCount(new uint(0)) // default constructor
    {
    }

    explicit my_shared_ptr(T* ptr) : ptr(ptr), refCount(new uint(1)) // constructor
    {
    }

    /*** Copy Semantics ***/
    my_shared_ptr(const my_shared_ptr& obj) // copy constructor
    {
        this->ptr = obj.ptr; // share the underlying pointer
        this->refCount = obj.refCount;
        if (nullptr != obj.ptr)
        {
            (*this->refCount)++; // if the pointer is not null, increment the refCount
        }

        return this;
    }

    my_shared_ptr& operator=(const my_shared_ptr& obj) // copy assignment
    {
        __cleanup__(); // cleanup any existing data

        // Assign incoming object's data to this object
        this->ptr = obj.ptr; // share the underlying pointer
        this->refCount = obj.refCount;
        if (nullptr != obj.ptr)
        {
            (*this->refCount)++; // if the pointer is not null, increment the refCount
        }
        return *this;
    }

    /*** Move Semantics ***/
    my_shared_ptr(my_shared_ptr&& dyingObj) // move constructor
    {
        this->ptr = dyingObj.ptr; // share the underlying pointer
        this->refCount = dyingObj.refCount;

        dyingObj.ptr = dyingObj.refCount = nullptr; // clean the dying object
    }

    my_shared_ptr& operator=(my_shared_ptr&& dyingObj) // move assignment
    {
        __cleanup__(); // cleanup any existing data

        this->ptr = dyingObj.ptr; // share the underlying pointer
        this->refCount = dyingObj.refCount;

        dyingObj.ptr = dyingObj.refCount = nullptr; // clean the dying object

        return *this;
    }

    uint get_count() const
    {
        return *refCount; // *this->refCount
    }

    T* get() const
    {
        return this->ptr;
    }

    T* operator->() const
    {
        return this->ptr;
    }

    T& operator*() const
    {
        return this->ptr;
    }

    ~my_shared_ptr() // destructor
    {
        __cleanup__();
    }

private:
    void __cleanup__()
    {
        (*refCount)--;
        if (*refCount == 0)
        {
            if (nullptr != ptr) delete ptr;
            delete refCount;
        }
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////
///
///
template<typename Func>
class MyPackagedTask;

//////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The MyPackagedTask class
///
template<typename Ret, typename... Args>
class MyPackagedTask<Ret(Args...)>
{
private:
    std::promise<Ret> promise_;
    std::function<Ret(Args...)> func_;

public:
    explicit MyPackagedTask(std::function<Ret(Args...)> func) : func_(std::move(func)) {}

    void operator()(Args&&... args)
    {
        try
        {
            promise_.set_value(func_(std::forward<Args>(args)...));
        }
        catch (...)
        {
            promise_.set_exception(std::current_exception());
        }
    }

    auto getFuture()
    {
        return promise_.get_future();
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////
/// \brief myAsync
/// \param policy
/// \param func
/// \param args
/// \return
///
template<typename Func, typename... Args>
std::future<typename std::result_of<Func(Args...)>::type> myAsync(std::launch policy, Func&& func, Args&&... args)
{
    assert(policy == std::launch::async && "only async is supported");

    using Result = typename std::result_of<Func(Args...)>::type;
    std::packaged_task<Result(Args...)> task(func);
    std::future<Result> future = task.get_future();
    std::thread t(std::move(task), args...);
    t.detach();
    return future;
}
#endif // SMART_PONITERS_H
