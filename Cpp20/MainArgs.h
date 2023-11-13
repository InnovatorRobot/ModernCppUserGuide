#ifndef MAINARGS_H
#define MAINARGS_H
#include <iostream>
#include <optional>

int mainSimulation(int argc, char** argv)
{
    if (argc != 4)
    {
        std::cerr << "programm can be called with 3 args\n";
        return 0;
    }
    auto first_num = std::atof(argv[1]);
    auto operatorr = argv[2];
    auto second_num = std::atof(argv[3]);

    return 0;
}

// Working with auto keyword

void test()
{
    double some_var{55.5};
    double& some_var_ref{some_var};

    auto y = some_var_ref;
    auto& z = some_var_ref;
    ++y;
    std::cout << "sizeof(some_var): " << sizeof(some_var) << "\n";         // 8
    std::cout << "sizeof(some_var_ref): " << sizeof(some_var_ref) << "\n"; // 8
    std::cout << "sizeof(y): " << sizeof(y) << "\n";                       // 8
    std::cout << "&some_var: " << &some_var << "\n";                       // 0xabc123
    std::cout << "&some_var_ref: " << &some_var_ref << "\n";               // 0xabc123
    std::cout << "&y: " << &y << "\n";                                     // 0x854369
    std::cout << "&z: " << &z << "\n";                                     // 0xabc123
    std::cout << "some_var: " << some_var << "\n";                         // 55,5
    std::cout << "some_var_ref: " << some_var_ref << "\n";                 // 55,5
    std::cout << "y: " << y << "\n";                                       // 56,5
    std::cout << "z: " << z << "\n";                                       // 56,5
}

void test2()
{
    const double some_other_var{44.3};
    const double& const_ref{some_other_var};
    auto& p = const_ref;
    std::cout << "some_other_var: " << some_other_var << "\n";
    std::cout << "const_ref: " << const_ref << "\n";
    std::cout << "p: " << p << "\n";

    // ++p compiler error
}

std::optional<int> find_char_v0(std::string str, char c)
{
    auto res = str.find(c);
    if (res != std::string::npos) return std::optional<int>{res};
    return std::nullopt;
}
#endif // MAINARGS_H
