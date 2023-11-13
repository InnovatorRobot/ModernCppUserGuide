#ifndef OVERLOADING_H
#define OVERLOADING_H
#include <cassert>
#include <iostream>

class MyPoint
{
    friend inline MyPoint operator+(MyPoint const& left, MyPoint const& right);
    friend std::ostream& operator<<(std::ostream& os, MyPoint const& MyPoint);
    friend std::istream& operator>>(std::istream& is, MyPoint const& MyPoint);
    friend MyPoint operator*(MyPoint const& left, MyPoint const& right);

public:
    MyPoint(double x, double y) : x_{x}, y_{y} {}

    //    MyPoint operator+(MyPoint const& other) const
    //    {
    //        return {MyPoint(this->x_ + other.x_, this->y_ + other.y_)};
    //    }

    /// Compound Operator ==>> += or -=

    void print()
    {
        std::cout << "x: " << x_ << " y: " << y_ << "\n";
    }

    double& operator[](size_t index) /// Subscript Operator!
    {
        assert(index == 0 || index == 1);
        return x_;
    }

    const double& operator[](size_t index) const
    {
        assert(index == 0 || index == 1);
        return x_;
    }

private:
    double x_;
    double y_;
};

inline MyPoint operator+(MyPoint const& left, MyPoint const& right) /// definition of non member operator function!
{
    return {MyPoint(left.x_ + right.x_, left.y_ + right.y_)};
}

inline std::ostream& operator<<(std::ostream& os, MyPoint const& MyPoint) /// Stream insertaion operation Operator!
{
    os << "MyPoint is: " << MyPoint.x_ << " " << MyPoint.y_ << "\n";
    return os;
}

// inline std::istream& operator>>(std::istream& is, MyPoint const& MyPoint) /// Stream Extraction Operator!
//{
//    double x;
//    double y;
//    is >> x;
//    is >> y;
//    MyPoint.x_ = x;
//    MyPoint.y_ = y;
//    return is;
//}

/// Arithmatisc operator ovberloading

// inline MyPoint operator*(MyPoint const& left, MyPoint const& right)
//{
//    return MyPoint{left.x_ * right.x_, left.y_ * right.y_};
//}

/// Compound Operators && Reusing Other Operators!
///
/// For example + can be implemeted in terms of +=
///
//
// inline MyPoint operator+=(MyPoint const& left, MyPoint const& right)
//{
//    left.x += left.x + right.x;
//    left.y += left.y + right.y;
//    return left;
//}

//
// inline MyPoint operator+(MyPoint const& left, MyPoint const& right)
//{
//    MyPoint p(left.x, left.y);
//    return p += left;
//}

/// Custom type conversion
///

class Number
{
    friend Number operator+(Number const& left, Number const& right);
    friend Number operator-(Number const& left, Number const& right);
    friend Number operator*(Number const& left, Number const& right);
    friend Number operator/(Number const& left, Number const& right);
    friend std::ostream& operator<<(std::ostream& os, Number const& number);
    friend void operator++(Number& number);
    friend void operator--(Number& number);

public:
    Number() = default;
    Number(int value) : value_{value} {}

    Number operator+(Number const& other) const
    {
        return Number(other.value_ + this->value_);
    }

    explicit operator double() const // whenever you use static_cast in you r function it will be called!
    {
        return static_cast<double>(value_);
    }

    explicit operator MyPoint() const // whenever you use static_cast in you r function it will be called!
    {
        return MyPoint{
            static_cast<double>(value_),
            static_cast<double>(value_),
        };
    }

    /// Unary ++ Postfix Overloading
    Number operator++(int)
    {
        return this->value_++;
    }

    int getNubmer() const
    {
        return value_;
    }

private:
    int value_{};
};

Number operator+(Number const& left, Number const& right)
{
    return Number(left.value_ + right.value_);
}

Number operator-(Number const& left, Number const& right)
{
    return Number(left.value_ - right.value_);
}

Number operator*(Number const& left, Number const& right)
{
    return Number(left.value_ * right.value_);
}

Number operator/(Number const& left, Number const& right)
{
    return Number(left.value_ / right.value_);
}

inline std::ostream& operator<<(std::ostream& os, Number const& number) /// Stream insertaion operation Operator!
{
    os << "MyPoint is: " << number.value_ << "\n";
    return os;
}

void testOverloadNumber()
{
    Number n1(22);
    std::cout << "n1: " << n1 << "\n";
    std::cout << "n1 + 2: " << 2 + n1 << "\n";
}

class DropPolicy
{
public:
    DropPolicy() = default;
    void operator()() /// Functors operator overloading
    {
        while (1)
        {
            std::cout << "Saman\n";
        }
    }
};

void testDropPolicy()
{
    DropPolicy dd;
    //    dd();
    Number nn(5);
    nn++;
    std::cout << nn.getNubmer() << "\n";
    ++nn;
    std::cout << nn.getNubmer() << "\n";
}

/// Unary ++ Prefix Overloading
inline void operator++(Number& number)
{
    number.value_++;
}

inline void operator--(Number& number)
{
    number.value_--;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // OVERLOADING_H
