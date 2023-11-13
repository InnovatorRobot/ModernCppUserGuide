#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <initializer_list>
#include <set>
#include <queue>
#include <deque>
class Cylinder
{
public:
    Cylinder() = default;
    // initialzer lists constructor: avoid potential compies!
    Cylinder(double rad, double height) : height_{height}, rad_{rad} {}
    auto volume() const
    {
        return height_ * rad_;
    }

    auto getHeight() const
    {
        return height_;
    }

    auto getRad()
    {
        return rad_;
    }

    double& getterSetterRad()
    {
        return rad_;
    }

    const double& getterSetterRad() const
    {
        return rad_;
    }

private:
    double rad_;
    double height_;
};

void testConstClass()
{
    const auto cylinder1 = Cylinder(2, 3);
    // auto rad = cylinder1.getRad(); compile error! we have to add const keyword after the getRad method!

    const auto cylinder2 = Cylinder(2, 3);
    // Cylinder *cylinder3 = &cylinder2; Error: invalid conversion from const *Cylinder to Cylinder
}

class Square
{
public:
    explicit Square(double side_param);

    Square(double side_param, const std::string& color_param, int shading_param)
        : side_param_(side_param), color_{color_param}, shading_{shading_param}
    {
    }
    ~Square();
    double surface() const;

private:
    double side_param_;
    std::string color_;
    int shading_;
};

/// Delegate object construction to other constructor!
Square::Square(double side_param) : Square(side_param, "red", 3) {}

/////////////////////////////////////////
///
///
/// Copy Constructors
class Person
{
private:
    std::string lastName_;
    std::string firstName_;
    int age_{};

public:
    Person() = default;
    Person(const std::string& first, const std::string& last, int age)
        : firstName_{first}, lastName_{last}, age_{age} {};
    // we are trying to copy by Person p2(p1);
    Person(const Person& source) : firstName_{source.firstName_}, lastName_{source.lastName_}, age_{source.age_} {}

    Person operator=(const Person& other)
    {
        this->age_ = other.age_;
        this->lastName_ = other.lastName_;
        this->firstName_ = other.firstName_;
        return *this;
    }
};

void testPerson()
{
    Person p1("saman", "mahmoodi", 29);
    Person p2(p1);
    Person p3 = p2;
    Person p4{"saman", " mahmoodi", 29};
}

/////////////////////////////////////
///
///
/// objects stored in arrays are copies!
/// Person students[] = {p1, p2, p3}
/// there are 6 Person objects now!

/////////////////////////////////////
///
///
/// Shallow copy: dont care about the pointer
/// Deep copy: care about the pointers!

/////////////////////////////////////////
///
///
/// Move Constructors

class Point
{
private:
    size_t x_{};
    size_t y_{};

public:
    Point() = default;
    Point(size_t x, size_t y) : x_{x}, y_{y} {}

    auto getX() const
    {
        return x_;
    }

    auto getY() const
    {
        return y_;
    }

    Point(const Point& source) : x_{source.getX()}, y_{source.getY()} {}

    Point(Point&& source)
        : x_{source.getX()},
          y_{source.getY()} {} // for forcing compiler use std::move at the time you are trying use the class
};
//////////////
///
///
/// Initializer List in Constructors:

class PointIL
{
public:
    PointIL(std::initializer_list<size_t> lists)
    {
        for (const auto& elem : lists)
        {
            std::cout << "elem: " << elem << "\n";
        }
        x_ = *(lists.begin());
        y_ = *(lists.begin() + 1);
    }

private:
    size_t x_;
    size_t y_;
};

void testPointIL()
{
    PointIL{1, 2, 3, 4, 5, 6, 7, 8};
}

////////////////////////////
///
/// Designated Initializer
///

struct Componenet
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
};

void testComponent()
{
    Componenet c1{.x = 5, .y = 6, .z = 7};
    // Componenet c2{.y = 5, .z = 6, .x = 7}; this is not working because the order has not been considered!
}

///////////////////
///
/// Narrowing Conversion has not been supported by uniform initialization!
/// Point p1(1.5, 2.5)
/// Point p2{1.5, 2.5}  --> Compile Error!

///////////////////
///
/// Friend Functions
///
class Dog
{
    friend std::string getDogName(const Dog& dog);
    friend class Cat;

public:
    Dog() = default;

private:
    std::string dogName_{"Mock"};
};

std::string getDogName(const Dog& dog)
{
    return dog.dogName_;
}

///////////////////
///
/// Friend Classes
///

class Cat
{
public:
    Cat()
    {
        number_++;
    }
    auto getDogName(const Dog& dog) const
    {
        return dog.dogName_;
    }
    auto getNumber() const
    {
        return number_;
    }

private:
    std::string catName_{"Persian"};
    static size_t number_;
};

size_t Cat::number_ = 0;

//////////////////////////
///
/// inline static memeber
class InlineStaticTest
{
public:
    InlineStaticTest()
    {
        counter_++;
    }

    auto getNumber()
    {
        return counter_;
    }

private:
    inline static size_t counter_{};
};

//////////////////////////
///
/// static constant
class StaticConstantTest
{
    friend auto getPI();
    friend auto getDummy();

public:
    StaticConstantTest() {}

private:
    static inline constexpr double PI{3.14159263};
    static constexpr double Dummy{0.123456};
};

auto getPI()
{
    return StaticConstantTest::PI;
}
auto getDummy()
{
    return StaticConstantTest::Dummy;
}

///////////////////////////////
///
/// Member variabels of self type

class SelfType
{
public:
    SelfType() : self(nullptr) {}
    static size_t number_;
    /// be aware of initilizing the Self type in constructor with new*! it causes the memroy leak!
private:
    /// compile errors due to not initializing the number_ member!
    //    SelfType self_;
    //    const SelfType selfConst_;
    //    static inline const SelfType selfStatic;
    /// we can define pointer instead of simple variable!
    SelfType* self;
};

//////////////////////////////////
///
/// Static Member Functions

class StaticMemberFunctionTest
{
    StaticMemberFunctionTest() = default;
    /// we can not have const keywork after static methods!
    static auto getNumber()
    {
        return number_;
    }

    static auto getNumber2(const StaticMemberFunctionTest& source)
    {
        return source.number2_;
    }

private:
    static inline size_t number_{}; // it has to be static to be useful in getNumber function!
    size_t number2_{};
};

/////////////////////////////////
///
/// Netsted Classes
#include <eigen3/Eigen/Eigen>
template<typename ToType>
struct ConvertTo
{
    template<typename FromType>
    static int from(FromType const&);
};

template<>
template<>
int ConvertTo<double>::from(const Eigen::Matrix<double, 5, 1>& v)
{
    return 0;
}

class Ouster
{
public:
    Ouster(uint8_t num1, uint8_t num2) : num1_{num1}, num2_{num2} {}

private:
    uint8_t num1_{};
    uint8_t num2_{};

    class Inner
    {
    public:
        explicit Inner(uint8_t num) : num_{num} {}
        //        auto getNum1()
        //        {
        //            return num1_; compile error!
        //        }
    private:
        uint8_t num_{};
    };
};

template<typename T>
struct Subject
{
    T value_;
};

template<typename T>
class MockSubject : public Subject<T>
{
public:
    void update(T a)
    {
        this->value_ = a;
    }
};

template<typename T>
using Type = std::set<T>;

template<typename T>
using Sweep = std::deque<std::queue<std::set<T>>>;

template<typename T>
class SweepCollector : Subject<Sweep<T>>
{
public:
    explicit SweepCollector(Subject<Type<T>>& subject) : val_{subject} {}
    Subject<Type<T>> val_;
};

using MockPointCloudSampleSubject = MockSubject<std::queue<std::set<int>>>;

#endif // CLASSES_H
