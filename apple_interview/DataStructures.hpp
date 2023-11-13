#ifndef DATASTRUCTURES_HPP
#define DATASTRUCTURES_HPP

#include <iostream>
#include <memory>

enum class Color
{
    Red = 0,
    Black = 1,
};

struct RBTNode
{
    RBTNode(int val, Color clr) : value{val}, color(clr) {}
    int value;
    std::unique_ptr<RBTNode> left = nullptr;
    std::unique_ptr<RBTNode> right = nullptr;
    Color color;
};

void insertInRBT(std::unique_ptr<RBTNode>& root, int value)
{
    if (root == nullptr)
    {
        root = std::make_unique<RBTNode>(value, Color::Black);
    }
    else
    {
        if (value < root->value)
        {
            insertInRBT(root->left, value);
        }
        else
        {
            insertInRBT(root->right, value);
        }
    }
}

#endif // DATASTRUCTURES_HPP
