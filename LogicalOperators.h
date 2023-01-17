#ifndef LOGICALOPERATORS_H
#define LOGICALOPERATORS_H
/// All Logical Operators
#include <utility>
#include "Overloading.h"
class LogicalPoint
{
public:
    LogicalPoint() = default;
    LogicalPoint(double x, double y) : x_{x}, y_{y} {}
    double getLength() const
    {
        return x_ * y_;
    }
    //    bool operator<(LogicalPoint const& other) const
    //    {
    //        return (this->getLength() < other.getLength());
    //    }
    //    bool operator>(LogicalPoint const& other) const
    //    {
    //        return (this->getLength() > other.getLength());
    //    }
    //    bool operator<=(LogicalPoint const& other) const
    //    {
    //        return (this->getLength() <= other.getLength());
    //    }
    //    bool operator>=(LogicalPoint const& other) const
    //    {
    //        return (this->getLength() >= other.getLength());
    //    }
    //    bool operator==(LogicalPoint const& other) const
    //    {
    //        return (this->getLength() == other.getLength());
    //    }
    //    bool operator!=(LogicalPoint const& other) const
    //    {
    //        return (this->getLength() != other.getLength());
    //    }

private:
    double x_;
    double y_;
};

using namespace std::rel_ops;
bool operator<(LogicalPoint const& left, LogicalPoint const& right)
{
    return (left.getLength() < right.getLength());
}

bool operator==(LogicalPoint const& left, LogicalPoint const& right)
{
    return (left.getLength() < right.getLength());
}

/// Logical Operators with implicit conversion
///
/// C++20
/// We are trying to compare integer number with Number Class
/// One solution is to use operator overload for each argument!
///
/// We can use C++20 feature!
#include <limits>
void testCpp20CompareFeature()
{
    int n1(1);
    int n2(2);
    auto result = (n1 <=> n2);
    std::cout << std::boolalpha;
    std::cout << (result > 0) << "\n";
    std::cout << (result >= 0) << "\n";
    std::cout << (result == 0) << "\n";
    std::cout << (result < 0) << "\n";
    std::cout << (result <= 0) << "\n";
    ///////////////////////////////////////////
    double d1{33.9};
    double d2{std::numeric_limits<double>::quiet_NaN()};
    std::cout << "d1 < d2: " << ((d1 <=> d2) < 0) << "\n";   // false
    std::cout << "d1 > d2: " << ((d1 <=> d2) > 0) << "\n";   // false
    std::cout << "d1 == d2: " << ((d1 <=> d2) == 0) << "\n"; // false
}
#endif // LOGICALOPERATORS_H
