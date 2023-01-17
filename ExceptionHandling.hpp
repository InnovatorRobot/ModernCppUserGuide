#ifndef EXCEPTIONHANDLING_HPP
#define EXCEPTIONHANDLING_HPP
#include <exception>
#include <iostream>

class SomethingIsWrong
{
public:
    explicit SomethingIsWrong(const std::string& message) : message_{message} {}
    virtual ~SomethingIsWrong() {}
    virtual const std::string what() const
    {
        return message_ + " RED";
    }

private:
    std::string message_;
};

void doSomething(int i)
{
    if (i == 2)
    {
        throw SomethingIsWrong("Saman ");
    }
    if (i == 3)
    {
        throw 3;
    }
}
void testException1()
{
    for (int i = 0; i < 4; ++i)
    {
        try
        {
            try
            {
                doSomething(i);
            }
            catch (SomethingIsWrong& ex)
            {
                if (typeid(ex) == typeid(SomethingIsWrong))
                {
                    std::cout << typeid(ex).name() << "Inner " << ex.what() << "\n";
                }
                else if (typeid(ex) == typeid(int))
                {
                    throw;
                }
            }
        }
        catch (int ex)
        {
            std::cout << ex << "\n";
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The ItemNoExcept class
/// Exception can niot be propagated out of a noecept function by any means, if you do so the program will terminate,
/// you van also see that compiler gives you a warning about that!
class ItemNoExcept
{
public:
    ItemNoExcept() = default;
    ~ItemNoExcept() noexcept(
        false) // Distructor are noexcep by default! If we want to propagate exception we should use noexcept(false)
    {
        throw 1;
    }
    void doSomethingInClass() const noexcept
    {
        std::cout << "Doing something from class\n";
        try
        {
            throw 1;
        }
        catch (int ex)
        {
            std::cout << "Handling exeption in ItemException::DoSomethingInClass \n";
            //            throw;
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Exception in C++ standard library!
/// logic_error: invalid_argument, length_error, out_of_range, future_error, domain_error
/// runtime_error: overflow_error, underflow_error, range_error, regex_error, system_error
/// others: bad_alloc, bad_cast, bad_optional_access
/// etc.
///

class AnimalException
{
public:
    explicit AnimalException(std::string const& name) : name_(name) {}
    virtual ~AnimalException() {}

    virtual std::string getName() const
    {
        return name_;
    }

private:
    std::string name_;
};

class FlineException : AnimalException
{
public:
    explicit FlineException(std::string const& name) : AnimalException(name) {}
    virtual ~FlineException() {}

    std::string getName() const override
    {
        return "Fline " + name_;
    }

private:
    std::string name_;
};

void testException2()
{
    AnimalException animal("Cat");
    try
    {
        FlineException& fline = dynamic_cast<FlineException&>(animal); // failed and throw exception!
    }
    catch (std::exception& ex)
    {
        std::cout << "Something is wrong " << ex.what() << "\n";
    }
}
#endif // EXCEPTIONHANDLING_HPP
