#ifndef METAPROGRAMMING_H
#define METAPROGRAMMING_H
#include <iostream>
#include <tuple>
#include <string>
#include <map>
#include <functional>
/// For doing something at compile time it is good to have Template MetaProgramming!
///
///

/// For TMP you have to do two things at the first: 1) Choosing good names, 2) Seprating out levels of abstractions
///
///

/// Purpos of the code:
/// Checks whether an exprission is valid for a given type or not!
///

/// For example Is valid to have incrememtal on type t or not like: ++t;
/// If t is int then it is valid otherwise it is not valid (like string)
///

/// Our goal is to have stuff like this: is_incrementable<T>::value
/// If you are not using C++17 then there is no void_t BUT you can use below for having:
/// template<typename...>
/// using void_t = void;
/// surrogate?

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

template<typename, typename = void>
struct is_incrementable : std::false_type
{
};

template<typename T>
struct is_incrementable<T, std::void_t<decltype(++std::declval<T&>())>> : std::true_type
{
};

void TestIncrementble()
{
    auto const check1 = is_incrementable<int>::value;
    std::true_type a;
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

template<int n>
struct FuncStruct /// FuncStruct<8>::val == 256
{
    enum
    {
        val = 2 * FuncStruct<n - 1>::val
    };
};

template<>
struct FuncStruct<0>
{
    enum
    {
        val = 1
    };
};

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

template<typename First, typename Second>
struct IsSameType
{
    enum
    {
        value = 0
    };
};

template<typename First>
struct IsSameType<First, First>
{
    enum
    {
        value = 1
    };
};

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

/// Adder for haveing adder function which calculate add in compile time
/// Adder<2, 3> would be calculated in compile time!
template<int T, int U>
struct Adder
{
    enum
    {
        value = T + U
    };
};

/// Same as above code!
template<int A, int B>
struct Adder2
{
    static constexpr int value{A + B};
};

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// std::move and std::forward
/// lvalue reference: T& x AND rvalue reference T&& x
///
/// lvalue, rvalue, glvalue, prvalue, xvalue
///
std::map<std::string, std::function<void()>> commands;
template<typename ftor>
void installCommand(std::string name, ftor&& handler)
{
    commands.insert({std::move(name), std::forward<ftor>(handler)});
}

class Test
{
public:
    Test()
    {
        std::cout << "ctor" << std::endl;
    }
    Test(const Test&)
    {
        std::cout << "copy ctor" << std::endl;
    }
    Test(Test&&)
    {
        std::cout << "move ctor" << std::endl;
    }
};

void func(Test const&)
{
    std::cout << "requires lvalue" << std::endl;
}

void func(Test&&)
{
    std::cout << "requires rvalue" << std::endl;
}

template<typename Arg>
void pass(Arg&& arg)
{
    // use arg here
    func(std::forward<Arg>(arg));
    return;
}

template<typename Arg, typename... Args>
void pass(Arg&& arg, Args&&... args)
{
    // use arg here
    return pass(std::forward<Args>(args)...);
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

void overloaded(int const& arg)
{
    std::cout << "by lvalue\n";
}

void overloaded(int&& arg)
{
    std::cout << "by rvalue\n";
}

template<typename T>
void forwarding(T&& arg)
{
    std::cout << "via std::forward: ";
    overloaded(std::forward<T>(arg));
    std::cout << "via std::move: ";
    overloaded(std::move(arg)); // conceptually this would invalidate arg
    std::cout << "by simple passing: ";
    overloaded(arg);
}

void testForward2()
{
    std::cout << "initial caller passes rvalue:\n";
    forwarding(5);
    std::cout << "initial caller passes lvalue:\n";
    int x = 5;
    forwarding(x);
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

/// The essence of the issue is that “&&” in a type declaration sometimes means rvalue reference, but sometimes it means
/// either rvalue reference or lvalue reference

template<typename T1, typename T2>
void inner(T1 t1, T2 t2);

template<typename T1, typename T2>
void outer(T1&& t1, T2&& t2)
{
    inner(std::forward<T1>(t1), std::forward<T2>(t2));
}
#endif // METAPROGRAMMING_H
