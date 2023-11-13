#include <iostream>
#include <chrono>
#include <vector>
/// Item 18: Use std::unique_ptr for exclusive-ownership resource management.
/// Item 19: Use std::shared_ptr for shared-ownership resource management.
// std::shared_ptrs are twice the size of a raw pointer
// Memory for the reference count must be dynamically allocated.
// Increments and decrements of the reference count must be atomic

/// Calculation time function invocation

void timeConsumingFunction(int number)
{
    while (number > 0)
    {
        int a = 5;
        number--;
    }
}
void testTimeFuncInvocation()
{
    auto timeFuncInvocation = [](auto&& func, auto&&... params)
    {
        auto startTime = std::chrono::system_clock::now();
        std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...);
        auto endTime = std::chrono::system_clock::now();
        std::cout << (endTime - startTime).count() << "\n";
    };
    std::string str_auto = "0x7f";

    timeFuncInvocation(timeConsumingFunction, 60);
    int i_auto = std::stoi(str_auto, nullptr, 0);
    std::cout << i_auto << "\n";
}

template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg)
{
    using ReturnType = typename std::remove_reference<T>::type&&;
    return static_cast<ReturnType>(arg);
}

template<typename T>
void someFunc(T&& param);

/// arbitrary function invocation
void testFuncRValue()
{
    // start timer
    auto timeFuncInvocation = [](auto&& func, auto&&... params)
    { std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...); };
    // end timer
}

/// Use std::move on rvalue references, std::forward on universal references.

/// If a function template parameter has type T&& for a deduced type T, or if an object is declared using auto&&, the
/// parameter or object is a universal reference

///
/*
 *
 *In C++, `std::decay` is a type trait defined in the `<type_traits>` header. It is used to apply lvalue-to-rvalue,
array-to-pointer, and function-to-pointer implicit conversions to a type, as well as to remove cv-qualifiers. The
resulting type is the type that you get when you pass an object to a function by value.

Here is what `std::decay` does to a type `T`:

1. If `T` is an array type, it is converted to a pointer type. This is equivalent to the array-to-pointer decay.
2. If `T` is a function type, it is converted to a pointer to function type. This is equivalent to the
function-to-pointer decay.
3. If `T` is a reference (lvalue reference or rvalue reference), the reference is removed.
4. If `T` is const or volatile, these qualifiers are removed.

The `std::decay` type trait is particularly useful in template metaprogramming when you want to ensure that a type is
treated the same way it would be as a function argument passed by value.

Here's an example to demonstrate `std::decay`:

```cpp
#include <type_traits>
#include <iostream>

int main() {
    typedef std::decay<int[]>::type A; // int*
    typedef std::decay<int(const volatile)>::type B; // int
    typedef std::decay<int&>::type C; // int
    typedef std::decay<int&&>::type D; // int
    typedef std::decay<int()>::type E; // int(*)()

    std::cout << std::boolalpha;
    std::cout << "Is A int*? " << std::is_same<A, int*>::value << std::endl;
    std::cout << "Is B int? " << std::is_same<B, int>::value << std::endl;
    std::cout << "Is C int? " << std::is_same<C, int>::value << std::endl;
    std::cout << "Is D int? " << std::is_same<D, int>::value << std::endl;
    std::cout << "Is E a function pointer? " << std::is_same<E, int(*)()>::value << std::endl;

    return 0;
}
```

The output should be:

```
Is A int*? true
Is B int? true
Is C int? true
Is D int? true
Is E a function pointer? true
```

This shows that `std::decay` correctly transforms the types according to the rules mentioned above.
 */
///
