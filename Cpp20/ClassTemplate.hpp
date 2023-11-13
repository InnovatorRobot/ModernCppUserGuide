#ifndef CLASSTEMPLATE_HPP
#define CLASSTEMPLATE_HPP
#include <type_traits>
#include <ostream>
template<typename T>
class PointClassTemplate
{
    static_assert(std::is_arithmetic_v<T>, "Coordinates of Point can only be numbers!"); // compile time check
    /// we can have std::is_default_constructible_v for checking a class has default constructor or not!
public:
    PointClassTemplate() = default;
    PointClassTemplate(T a, T b) : a_{a}, b_{b} {}

    friend std::ostream& operator<<(std::ostream& out, PointClassTemplate<T> const operand)
    {
        out << "Point is : " << operand.a_ << " " << operand.b_ << "\n";
        return out;
    }

private:
    T a_;
    T b_;
};

/// Use Concept in C++20 instead of static_assert!

template<typename T>
concept ArithmaticType = std::is_arithmetic_v<T>;

template<ArithmaticType T>
class PointClassTemplateConcept
{
public:
    PointClassTemplateConcept() = default;
    PointClassTemplateConcept(T a, T b) : a_{a}, b_{b} {}

    friend std::ostream& operator<<(std::ostream& out, PointClassTemplateConcept<T> const operand)
    {
        out << "Point is : " << operand.a_ << " " << operand.b_ << "\n";
        return out;
    }

private:
    T a_;
    T b_;
};

template<typename T>
requires std::is_default_constructible_v<T>
class BoxContainter
{
public:
    BoxContainter(const BoxContainter<T>& source) requires std::copyable<T>;
    BoxContainter(size_t size) {}
};

#endif // CLASSTEMPLATE_HPP
