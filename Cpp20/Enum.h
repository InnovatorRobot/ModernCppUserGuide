#ifndef ENUM_H
#define ENUM_H
#include <iostream>
#include <array>
enum class Month
{
    Jan,
    January = Jan,
    Feb,
    February = Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};

enum class MonthChar : unsigned char
{
    Jan = 0,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};

Month month{Month::Apr};
MonthChar monthchar{MonthChar::Jan};
extern "C" void printEnum()
{
    std::cout << static_cast<int>(month);
    std::cout << sizeof(month);
}

std::string_view usingEnum(Month month)
{
    switch (month)
    {
        // C++20 feature
        using enum Month;
        case Jan: return "Januery";
        default: return "None";
    }
}

enum class Direction
{
    TopLeft,
    TopRight,
    Center,
    BottomLeft,
    BottomRight
};

enum class Tool
{
    Pen,
    Marker,
    Eraser,
    Rectangle,
    Circle,
    PaintBicket
};

void TestEnum(Direction direction, Tool tool)
{
    std::cout << "direction is: " << static_cast<int>(direction) << "\n";
    std::cout << "tool is: " << static_cast<int>(tool) << "\n";
    //    std::cout << "tool < direction" << (tool > direction) << "\n";
}

class Base1
{
public:
    Base1(int value) : value_(value) {}
    int value_;
};

template<typename T, int Name>
class Base2
{
public:
    using Type = T;

    constexpr Base2() noexcept = default;

    constexpr explicit Base2(Type const& value) : value_{value} {}
    constexpr explicit Base2(Type&& value) : value_{std::move(value)} {}

    constexpr operator Type&()
    {
        return value_;
    }
    constexpr operator Type const &() const
    {
        return value_;
    }

private:
    Type value_;
};

template<typename T>
class Base3 : public T
{
public:
    Base3() = default;
    using Covariance = std::array<int, 3>;
    template<typename U>
    Base3(U&& u, Covariance covariance) : T{std::forward<U>(u)}, covariance_(std::move(covariance))
    {
    }
    auto covariance() const
    {
        return covariance_;
    }

private:
    Covariance covariance_;
};

template<typename T>
class CovarianceCalculation : private T
{
public:
    using Type = T;
    using Covariance = typename T::Covariance;
    CovarianceCalculation(T value) : T(value) {}
    auto covariance() const
    {
        return T::covariance();
    }
};

void TestClass()
{
    using GnssPose = Base2<Base1, 2>;
    using GnssPoseWithCovariance = Base3<GnssPose>;
    using CC = CovarianceCalculation<GnssPoseWithCovariance>;
    GnssPoseWithCovariance::Covariance cov;
    cov[0] = 1;
    cov[1] = 2;
    cov[2] = 3;
    auto ss = CC{GnssPoseWithCovariance{GnssPose{Base1{5}}, cov}};
    auto temp = ss.covariance();
}
#endif // ENUM_H
