#ifndef NAMESPACE_H
#define NAMESPACE_H
#include <iostream>
#include <string>
std::string getFamily()
{
    return "Mahmoodi";
}
void printMyName()
{
    std::cout << "Mohi";
}

namespace myspace
{
    std::string getFirstName()
    {
        return "Saman";
    }
    void printMyName()
    {
        std::cout << ::getFamily() + getFirstName();
        ::printMyName();
    }

} // namespace myspace

namespace Level1::Level2::Level3
{
    double dummy{};
}

void testNameSpace()
{
    namespace Data = Level1::Level2::Level3;
    Data::dummy = 5.5;
}
#endif // NAMESPACE_H
