#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

/*
 *
std::enable_if is a type trait that is used in C++ template metaprogramming to conditionally enable or disable function
overloads, class specializations, or member functions based on compile-time boolean expressions. It can be seen as a way
to implement SFINAE (Substitution Failure Is Not An Error) which is a key concept in C++ template programming.

When std::enable_if's boolean expression is true, it defines a member typedef type, which is typically used as a return
type or a template parameter. When the boolean expression is false, type is not defined, which causes a substitution
failure in the template, but, importantly, this is not considered an error.

Here's how you might use std::enable_if:
 *
 */
#include <iostream>

#include <type_traits>

template<typename T>
typename std::enable_if<std::is_integral_v<T>, bool>::type is_odd(T i)
{
    return bool(i % 2);
}

template<typename T>
typename std::enable_if<std::is_floating_point_v<T>, bool>::type is_odd(T i)
{
    return bool(i % 2);
}

/// As a template parameter
///
#include <type_traits>

template<typename T, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
T half(T i)
{
    return i / 2;
}

/// As a Class Template Specialization

template<class T, class Enable = void>
class A; // Undefined general template

template<class T>
class A<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
public:
    void print() const
    {
        std::cout << "Floating point type.\n";
    }
};

template<class T>
class A<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
public:
    void print() const
    {
        std::cout << "Integral type.\n";
    }
};

void testEnable()
{
    auto const a1 = A<int>();
    a1.print();
    auto const a2 = A<double>();
    a2.print();
}
#endif // ENABLE_IF_HPP
