//#include "Cpp20/Classes.h"
//#include "Cpp20/MainArgs.h"
//#include "Cpp20/Enum.h"
//#include <ranges>
//#include <vector>
//#include <iostream>
//#include "Cpp20/MetaProgramming.h"
//#include <set>
//#include <iterator>
//#include "Cpp20/Overloading.h"
//#include "Cpp20/LogicalOperators.h"
#include "Cpp20/ExceptionHandling.hpp"
#include "Cpp20/Polymorphism.hpp"
#include "extern/cereal.hpp"
#include "stl/priority_queue.hpp"
#include "extern/fmt.hpp"
#include "extern/spdlog.hpp"
#include "Cpp20/ClassTemplate.hpp"
#include "Cpp20/MoveSemantic.hpp"
#include "Cpp20/FunctionEntity.hpp"
#include "effective_cpp/deducing_types.hpp"
#include "effective_cpp/enable_if.hpp"

#include "TheModernCppChallenge/math_problem.hpp"
#include "TheModernCppChallenge/language_features.hpp"
#include "TheModernCppChallenge/StringAndRegularExperissions.hpp"

#include "apple_interview/algorithms.hpp"

#include "multithreading/promise_future_packaged.hpp"
#include "multithreading/concurrency.hpp"

#include <list>
#include <variant>
#include <vector>
#include <thread>
#include <future>

//#include <format.h>

/*
 any
 decay
 filesystem
 byte

 STL parallelism

 Network programming
 Multithreading

 Design Patterns
 */
using namespace std;

struct X
{
    X()
    {
        std::cout << "ctor\n";
    }
    X(X const& x)
    {
        std::cout << "cctor\n";
    }
    X const& operator=(X const& x)
    {
        std::cout << "assign\n";
        return *this;
    }
};
using namespace std::ranges;

std::vector<int> const vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

template<size_t Id>
struct Input
{
    double value;

    bool operator==(Input const& rhs) const
    {
        return value == rhs.value;
    }
};

template<int a>
struct isodd
{
    static constexpr bool value = a % 2;
};

template<int a>
struct iseven
{
    static constexpr bool value = !(a % 2);
};

constexpr int compute(int v)
{
    return v * v * v;
}
///
/// constinit forces constant initialization of static or thread-local variables. It can help to limit static order
/// initialization fiasco by using precompiled values and well-defined order rather than dynamic initialization and
/// linking order…
constinit int global = compute(10);
void CPP20()
{
    //    age->Eat();
    //    int a;
    //    std::string str{"saman"};
    //    auto res = find_char_v0(str, 'z');

    //    Transform<double> aa;
    //    aa.a = 5;
    //    aa.b = -5;
    //    FramesPack<int, double> a{aa};
    //    setPose(a);
    //    X x;
    //    X xx{x};
    //    X xxx = x;
    //    xxx = xx;
    //    X xxxx = std::move(x);
    //    xx = std::move(xxx);
    //    TestClass();
    //    std::cout << "Hello, World!" << std::endl;
    //    for (auto& i : vec | views::reverse)
    //    {
    //        std::cout << i << ",";
    //    }

    //    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
    //    {
    //        std::cout << *it << ",";
    //        //                if (res.back() == lastElement)
    //        //                    return res;
    //    }

    //    pass(std::move<Test>(Test()));
    //    testForward2();
    //    std::multiset<int, std::greater<int>> s;
    //    auto sss = Input<0>{21};
    //    cout << 22 / 5 * 3;
    //    testDropPolicy();
    //    testCpp20CompareFeature();
    //    testPolymorphism();
    //    testCereal();
    //    testPriorityQueue();
    //    testCereal();
    //    testPolyPoint();
    //    testException1();
    //    testFMT();
    //    test_spdlog();
    //    thirdTestMoveSemantic();

    testFunctionEntity5();
    global = 100;
}

string getKey(string str)
{
    vector<int> count(26);
    for (int j = 0; j < str.size(); j++)
    {
        count[str[j] - 'a']++;
    }

    string key = "";
    for (int i = 0; i < count.size(); i++)
    {
        key.append(to_string(count[i]) + '#');
    }
    return key;
}

vector<int> topKFrequent(vector<int>&& nums, int k)
{
    map<int, int> m;
    vector<int> res;
    for (auto const num : nums)
    {
        m[num]++;
    }

    int counter = 0;
    for (auto [key, value] : m)
    {
        if (counter == k) break;
        res.push_back(key);
        counter++;
    }
    return res;
}

class Device
{
public:
    Device()
    {
        std::cout << "Device\n";
    }
    virtual void print()
    {
        std::cout << "Device" << std::endl;
    }
};

class Printer : public Device
{
public:
    Printer()
    {
        std::cout << "Printer\n";
    }
    void print() override
    {
        std::cout << "Printer" << std::endl;
    }
};

class Scanner : public Device
{
public:
    Scanner()
    {
        std::cout << "Scanner\n";
    }
    void print() override
    {
        std::cout << "Scanner" << std::endl;
    }
};

class Final : public Printer, public Scanner
{
public:
    Final()
    {
        std::cout << "Final\n";
    }
};

Device* func()
{
    return static_cast<Printer*>(new Final());
}

class Localization
{
public:
    Localization(int& a) : a_(a) {}

    int getInt()
    {
        return a_;
    }

    void setInt(int a)
    {
        a_ = a;
    }

private:
    int& a_;
};

class Env
{
public:
    Env(int&& a) : a_(a), loc(a) {}

    int getInt()
    {
        return a_;
    }

    void setInt(int a)
    {
        a_ = a;
    }

    Localization loc;

private:
    int& a_;
};

int main()
{
    //    CPP20();
    //    using FirstType = Type<int>;
    //    using SecondType = Type<char>;
    //    using namespace std::chrono_literals;

    //    FirstType firstElement{Stamped<int>{10, 1}, Stamped<int>{2, 2}, Stamped<int>{2, 3},
    //                           Stamped<int>{4, 4},  Stamped<int>{3, 5}, Stamped<int>{6, 6}};

    //    SecondType secondElement{Stamped<char>{11, 'A'}, Stamped<char>{2, 'A'}, Stamped<char>{3, 'A'}, Stamped<char>{4, 'A'}};

    //    std::tuple<FirstType, SecondType> tuples{firstElement, secondElement};

    //    std::cout << doMuStuff(tuples);
    //    std::cout << "----------------\n";
    //    std::apply(
    //        [](auto&&... args) {
    //            (std::for_each(args.begin(), args.end(), [](auto const value) { std::cout << value.value() << "\n";
    //            }), ...);
    //        },fib
    //        tuples);

    //    EffectiveCpp();
    //    testTimeFuncInvocation();
    //    printPI();
    //    testIPV41();
    //    testBinaryToString();

    //    l(argestSumSubArray();
    //    Matrix mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    //    rotateMatrixClockWise(mat);

    //    auto res = topKFrequent({4, 1, -1, 2, -1, 2, 3}, 2);
    //    testMultithreadQueue();

    Env env(1);
    std::cout << "env :" << env.getInt() << "\n";
    std::cout << "loc :" << env.loc.getInt() << "\n";
    env.setInt(5);
    std::cout << "env :" << env.getInt() << "\n";
    std::cout << "loc :" << env.loc.getInt() << "\n";
    env.loc.setInt(10);
    std::cout << "env :" << env.getInt() << "\n";
    std::cout << "loc :" << env.loc.getInt() << "\n";

    std::variant<int, int, int> vv;
    testEnable();
    return 0;
}
