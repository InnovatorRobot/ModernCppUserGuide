#ifndef POLYMORPHISM_HPP
#define POLYMORPHISM_HPP
#include <iostream>
#include <memory>

class Animal
{
public:
    Animal() = default;
    explicit Animal(const std::string_view& description) : description_(description) {}
    virtual ~Animal()
    {
        std::cout << "Animal Destructor\n";
    }

    virtual void breath() const
    {
        std::cout << "Animal breath called for : " << description_ << "\n";
    }

protected:
    std::string description_;
};

class Feline : public Animal
{
public:
    Feline() = default;
    explicit Feline(std::string_view const& m_fur_style, const std::string_view& description)
        : m_fur_style_(m_fur_style), Animal(description)
    {
    }
    ~Feline()
    {
        std::cout << "Feline Destructor\n";
    }

    virtual void run() const
    {
        std::cout << "Feline : " << description_ << "is running...\n";
    }

    void doSomeFelineThing()
    {
        std::cout << "Doing some feline thingy...\n";
    }
    std::string m_fur_style_;
};

class Dog : public Feline
{
public:
    Dog() = default;
    Dog(std::string_view const& fur_style, std::string_view const& description) : Feline(fur_style, description) {}
    ~Dog()
    {
        std::cout << "Dog Destructor\n";
    }
    virtual void bark() const
    {
        std::cout << "Dog::bark called : Woof! \n";
    }

    virtual void breath() const override
    {
        std::cout << "Dog::breath called for : " << description_ << "\n";
    }
};

class Cat : public Feline
{
public:
    Cat() = default;
    Cat(std::string_view const& fur_style, std::string_view const& description) : Feline(fur_style, description) {}
    virtual ~Cat()
    {
        std::cout << "Cat Destructor\n";
    }
    virtual void miaw() const
    {
        std::cout << "Dog::miaw called for cat!" << description_ << "\n";
    }

    virtual void breath() const override
    {
        std::cout << "Cat::breath called for : " << description_ << "\n";
    }
};

class Bird : public Animal
{
public:
    Bird() = default;
    Bird(std::string_view const& wing_color, std::string_view const& description)
        : wing_color_(wing_color), Animal(description)
    {
    }
    ~Bird() {}
    virtual void fly() const
    {
        std::cout << "Bird::fly called for bird!" << description_ << "\n";
    }

private:
    std::string_view wing_color_;
};

class Crow : public Bird
{
public:
    Crow() = default;
    Crow(std::string_view const& wing_color, std::string_view const& description) : Bird(wing_color, description) {}
    ~Crow() {}
    virtual void cow() const
    {
        std::cout << "Crow::cow called for crow!" << description_ << "\n";
    }

    virtual void breath() const override
    {
        std::cout << "Crow::breath called for : " << description_ << "\n";
    }
};

void testPolymorphism()
{
    Dog dog1("dark gray", "dog1");
    Cat cat1("black strips", "cat1");
    Crow crow1("black", "crow1");

    Animal* animals[]{&dog1, &cat1, &crow1};

    for (auto const& animal : animals)
    {
        animal->breath();
    }

    std::cout << "-----------------------\n";

    Dog dog2("dark gray", "dog2");
    Cat cat2("black strips", "cat2");

    Feline* felines[]{&dog2, &cat2};

    for (auto const& filine : felines)
    {
        filine->run();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Static in Polymorphism
///
///
class Shape
{
public:
    Shape() = default;
    explicit Shape(std::string const& description) : description_(description)
    {
        m_count_++;
    }

    virtual ~Shape() {}

    void draw() const
    {
        std::cout << "Shape::Draw called for: " << description_ << "\n";
    }

    virtual int getCount() const
    {
        return m_count_;
    }
    static int m_count_;

private:
    virtual void func() const
    {
        std::cout << "func Shape\n";
    }

protected:
    std::string description_;
};

int Shape::m_count_{};

class Ellipse : public Shape
{
public:
    Ellipse() = default;
    Ellipse(double x, double y, const std::string& description) : x_(x), y_(y), Shape(description)
    {
        m_count_++;
    }

    ~Ellipse() {}
    virtual int getCount() const override
    {
        return m_count_;
    }
    inline static int m_count_{};

    virtual void func() const override
    {
        std::cout << "func Ellipse\n";
    }
    double x_{};
    double y_{};
};

void testPolymorphism2()
{
    std::shared_ptr<Shape> shapes[] = {std::make_shared<Shape>("Shape1"), std::make_shared<Ellipse>(1, 2, "Ellipse1")};

    for (auto const& shape : shapes)
    {
        std::cout << shape->getCount() << " ";
        shape->draw();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///
///
/// Final in Polymorphism
///
/// We can put final keyword in the end of function name which we have overrided it! and also in the end of class name!
///

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///
///
/// Dynamic Cast
///
/// Is a facility in C++ to do down stream transformation between our polymorphic types
///
/// Benefit: Makes it possible to call non polymorphic methods on derived objects

void testPolymorphism3()
{
    Animal* animal1 = new Feline{"strips", " feline1"};
    Feline feline2("strips", "feline2");
    Animal& animal_ref = feline2;

    /// if the cast succeeds, we get a valid pointer back, if it fails, we get nullptr. So we can check before calling
    /// stuff on the returned pointer
    Feline* felinePtr = dynamic_cast<Feline*>(animal1);
    if (felinePtr)
    {
        felinePtr->doSomeFelineThing();
    }
    delete animal1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///
///
/// Dont call virtual(polymmorphic) functions from constructors and desctructors
/// NEVER
///
///

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///
///
/// typeid() operator
///
/// We can use and ask a base pointer which  kind of derived object it is managing at given moment in time!
///
/// Works only for polymorphism types
///
/// Return the dynamic type if it can and static type otherwise

/// Abstrcat Classees as Interfaces
/// Just pure virtual functions and without members!
///
///
class StreamInsertable
{
    friend std::ostream& operator<<(std::ostream& out, const StreamInsertable& operand);

public:
    virtual void stream_insert(std::ostream& out) const = 0;
};

std::ostream& operator<<(std::ostream& out, const StreamInsertable& operand)
{
    operand.stream_insert(out);
    return out;
}

class PolyPoint : public StreamInsertable
{
public:
    PolyPoint() = default;
    PolyPoint(double x, double y) : x_{x}, y_{y} {}

    virtual void stream_insert(std::ostream& out) const override
    {
        out << "Point[X: " << x_ << ", y: " << y_ << "]\n";
    }

private:
    double x_{};
    double y_{};
};

void testPolyPoint()
{
    PolyPoint p(2, 3);
    std::cout << p;
    operator<<(std::cout, p);
}
#endif // POLYMORPHISM_HPP
