#ifndef MOVESEMANTIC_HPP
#define MOVESEMANTIC_HPP
#include <iostream>
#include <type_traits>
#include <memory.h>
#include "BoxContainer.hpp"
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>
#include <fmt/os.h>
#include <fmt/color.h>

/// avoid unnessesary copies by move semantic

/// lvalue and rvalue

// lvalue -> are things you can grab an address for and use at a later time
// rvalue -> are transient or temporary in nature, they only exist for a short time and are quickly destroy by the
// system when no longer needed!

int moveSemanticeAdd(int x, int y)
{
    return x + y;
}

void firstTestMoveSemantic()
{
    int x = 5;
    int y = 5;
    // &(x+y) is incorrect!
}
/// Rvalue reference
void secondTestMoveSemantic()
{
    int x = 4;
    int y = 5;
    int&& outcome = x + y; // it means we dont want to destroy the address of (x+y) after calculation!
    int&& result =
        moveSemanticeAdd(x, y); // it means we dont want to destroy the address of moveSemanticeAdd after calculation!
    fmt::print("{}", outcome);
}

void thirdTestMoveSemantic()
{
    auto populate_box = [](BoxContainer<int>& box, int modifier)
    {
        for (size_t i{0}; i < 20; ++i)
        {
            box.add((i + 1) * modifier);
        }
    };

    auto make_box = [&populate_box](int modifier)
    {
        BoxContainer<int> local_int_box(20);
        populate_box(local_int_box, modifier);
        return local_int_box;
    };

    BoxContainer<int> box_array[2];

    std::cout << "--------" << std::endl;

    for (size_t i{0}; i < 2; ++i)
    {
        box_array[i] = make_box(i + 1); // Move assignment operator called
    }

    std::cout << "--------" << std::endl;
}

/// std::move does not move data by itself, it just casts its parameter to an rvalue
///
template<class T>
void swap(T& a, T& b)
{
    T temp{std::move(a)};
    a = std::move(b);
    b = std::move(temp);
}

#endif // MOVESEMANTIC_HPP
