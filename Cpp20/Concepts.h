#ifndef CONCEPTS_H
#define CONCEPTS_H
#include <concepts>

template<typename T>
concept MyIntegral = std::is_integral_v<T>;

template<typename T>
requires MyIntegral<T> T add(T a, T b)
{
    return a + b;
}

template<typename T>
concept MyFloat = std::is_floating_point_v<T>;

template<typename T>
requires MyFloat<T> T add(T a, T b)
{
    return a + b;
}

template<typename T>
concept Incrementable = requires(T a)
{
    a += 1;
    ++a;
    a++;
};

template<typename T>
concept Multipliable = requires(T a, T b)
{
    a* b;
};

template<typename T>
requires Incrementable<T> T add(T a, T b)
{
    return a + b;
}

///// Simple Reuirements, Nested Requirements, Compound Requirenments, Type requirenments
///
///

template<typename T>
concept TinyType = requires(T a)
{
    sizeof(T) <= 4;          // only check synteax: Simple req
    requires sizeof(T) <= 4; // Nested reuirement: chekc the if the experision is true!
};

/////////////////// Concept in Classes
///
///

template<typename T>
requires std::is_arithmetic_v<T>
class PointConcept1
{
public:
    PointConcept1() = default;
    PointConcept1(T x, T y) : x_{x}, y_{y} {}

private:
    T x_;
    T y_;
};

template<typename T>
concept Type = requires
{
    std::is_arithmetic_v<T>;
};

template<Type T>
class PointConcept2
{
public:
    PointConcept2() = default;
    PointConcept2(T x, T y) : x_{x}, y_{y} {}

private:
    T x_;
    T y_;
};

#endif // CONCEPTS_H
