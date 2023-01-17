#ifndef TREES_HPP
#define TREES_HPP
#include <vector>
#include <memory>
#include <functional>
#include <queue>
#include <cassert>

/* The problem:
Given a binary tree, implement a column-order traversal.

Each node is in a column, either -1 (left child) or +1 (right child)
from its parent. Nodes in the same column should be traversed by
distance from the root and by their value if the distance also matches.
*/

// Tree node type
struct Node
{
    int value = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

// Tree type, root is the root node of the tree
struct Tree
{
    Tree(const std::vector<int>& in);
    Node* root = nullptr;

private:
    std::vector<std::unique_ptr<Node>> nodes;
};

// Your solution:
void column_order(const Tree& tree, std::function<void(Node*)> visitor)
{
    /*
    for (node) {
        visitor(node);
    }
*/
}

void testTree1()
{
    std::vector<std::pair<std::vector<int>, std::vector<int>>> test_cases;
    test_cases.push_back({{1, 2, 3, 4, 5}, {4, 2, 1, 5, 3}});
    test_cases.push_back({{1, 2, 3, -1, 4, 5, -1, -1, 7, 6, -1, 9, -1, -1, 8}, {2, 6, 1, 4, 5, 8, 9, 3, 7}});
    test_cases.push_back({{1, 2, 3, 4, 5, 6, 7}, {4, 2, 1, 5, 6, 3, 7}});
    test_cases.push_back({{1, 2, -1, 3, -1, 4, -1}, {4, 3, 2, 1}});
    test_cases.push_back({{1, -1, 2, -1, 3, -1, 4}, {1, 2, 3, 4}});

    for (auto& tc : test_cases)
    {
        Tree t(tc.first);
        std::vector<int> data;
        column_order(t, [&data](Node* node) { data.push_back(node->value); });
        assert(std::ranges::equal(tc.second, data));
    }
}

// Support code
Tree::Tree(const std::vector<int>& in)
{
    if (in.empty()) return;

    std::queue<Node*> q;
    auto it = in.begin();
    nodes.push_back(std::make_unique<Node>(*it, nullptr, nullptr));
    q.push(nodes.back().get());
    root = q.front();
    it++;

    while (it != in.end())
    {
        if (*it > 0)
        {
            auto left = std::make_unique<Node>(*it, nullptr, nullptr);
            q.front()->left = left.get();
            q.push(left.get());
            nodes.push_back(std::move(left));
        }
        it++;

        if (it == in.end()) break;
        if (*it > 0)
        {
            auto right = std::make_unique<Node>(*it, nullptr, nullptr);
            q.front()->right = right.get();
            q.push(right.get());
            nodes.push_back(std::move(right));
        }
        it++;

        q.pop();
    }
}
#endif // TREES_HPP
