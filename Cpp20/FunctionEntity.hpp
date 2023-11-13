#ifndef FUNCTIONENTITY_HPP
#define FUNCTIONENTITY_HPP
#include <iostream>
#include <fmt/os.h>
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
/// Function pointer: is being used when we are working with callback function
///
///

void func2();
template<typename T>
T f(T a)
{
    return a;
}

double addNunmber(double const a, double const b)
{
    return a + b;
}

void testFunctionEntity1()
{
    double (*f_ptr)(double, double) = &addNunmber;
    //    double (*f_ptr)(double, double) = addNunmber;
    //    double (*f_ptr)(double, double){&addNunmber};
    //    double (*f_ptr)(double, double){addNunmber};

    //    auto f_ptr = &addNunmber;
    //    auto f_ptr = addNunmber;
    //    auto* f_ptr{&addNunmber};
    //    auto* f_ptr{addNunmber};
    fmt::print("Sum is {}", f_ptr(5, 10));
}

/// Callback function
///
// /
char encrypt(const char& param)
{
    return static_cast<char>(param + 3);
}

char decrypt(const char& param)
{
    return static_cast<char>(param - 3);
}

std::string& modify(std::string& str_param, char (*modifier)(const char&)) // auto modifier
{
    for (size_t i{}; i < str_param.size(); ++i)
    {
        str_param.at(i) = modifier(str_param.at(i));
    }
    return str_param;
}

/// alias
///
///
template<typename T>
using compare_T = bool (*)(const T&, const T&);

/// Functors
///
/// This is good for callback function

class Encrypt // This is the way which we call it functor! making a class and useing the operator overloading () to act as function!
{
public:
    char operator()(const char& param)
    {
        return static_cast<char>(param + 3);
    }
};

class Decrypt
{
public:
    char operator()(const char& param)
    {
        return static_cast<char>(param - 3);
    }
};

void testFunctionEntity2()
{
    Encrypt encrypt_class;
    fmt::print("encrypt of A is {}", encrypt_class('A'));
}

void testFunctionEntity3()
{
    auto functor = []<typename Modifier>(std::string str_param, Modifier modifier)
    {
        for (size_t i{}; i < str_param.size(); ++i)
        {
            str_param.at(i) = modifier(str_param.at(i));
        }
        return str_param;
    };

    Encrypt encrypt_class;
    auto encryptedString = functor("Saman", encrypt_class);
    fmt::print("encrypt of Saman is {}\n", encryptedString);

    Decrypt decrypt_class;
    auto deccryptedString = functor(encryptedString, decrypt_class);
    fmt::print("deccryptedString: {}\n", deccryptedString);
}

/// Standard Functos
///
///

void testFunctionEntity4()
{
    std::plus<int> adder;
    std::minus<int> substractor;
    std::greater<double> compare_greater;

    fmt::print("Adder functor: {}", adder(10, 7));
}

/// Functors with parameterss
///
///
template<typename T>
requires std::is_arithmetic_v<T>
class IsInRange
{
public:
    IsInRange(T min, T max) : min_{min}, max_{max} {}
    bool operator()(const T value) const
    {
        return ((value >= min_) && (value <= max_));
    }

private:
    T min_{};
    T max_{};
};

template<typename T, typename RangePicker>
requires std::is_arithmetic_v<T> T rangeSum(const std::vector<int>& vec, RangePicker isInRange)
{
    T sum{};
    std::for_each(
        vec.begin(), vec.end(),
        [&](auto const elem)
        {
            if (isInRange(elem))
            {
                sum += elem;
            }
        });
    return sum;
}

void testFunctionEntity5()
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    IsInRange<int> isInRange{3, 6};
    auto const result = rangeSum<int>(vec, isInRange);
    fmt::print("Sum of in range is: {}", result);
}

#endif // FUNCTIONENTITY_HPP
