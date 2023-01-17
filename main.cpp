//#include "Classes.h"
//#include "MainArgs.h"
//#include "Enum.h"
//#include <ranges>
//#include <vector>
//#include <iostream>
//#include "MetaProgramming.h"
//#include <set>
//#include <iterator>
//#include "Overloading.h"
//#include "LogicalOperators.h"
#include "ExceptionHandling.hpp"
#include "Polymorphism.hpp"
#include "extern/cereal.hpp"
#include "stl/priority_queue.hpp"
#include "extern/fmt.hpp"
#include "extern/spdlog.hpp"

#include <vector>

//#include <format.h>

/*
 variant
 optional
 any
 decay
 filesystem
 byte

 STL parallelism
 Fold experission
 meta programming

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
int main()
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
    test_spdlog();

    global = 100;

    return 0;
}
