#include <iostream>
#include <algorithm>
#include <functional>
#include <list>
#include <cassert>
#include <map>
#include <stack>
#include <limits>

namespace apple_detail
{
    struct Node
    {
        int data;
        std::list<Node*> neighbour;
        explicit Node(int d) : data{d} {}
    };

    struct ListNode
    {
        ListNode(int d) : data{d} {}
        int data;
        ListNode* next = nullptr;
    };

    struct TreeNode
    {
        int data;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        explicit TreeNode(int d) : data{d} {}
    };

    //    auto newNode(int data)
    //    {
    //        ListNode* node = new ListNode;
    //        node->data = data;
    //        return node;
    //    }
    //    void insertNewNode(ListNode** root, int data)
    //    {
    //        ListNode* node = newNode(data);
    //        ListNode* ptr;
    //        if (*root == NULL)
    //        {
    //            *root = node;
    //        }
    //        else
    //        {
    //            ptr = *root;
    //            while (ptr->next != NULL)
    //            {
    //                ptr = ptr->next;
    //            }
    //            ptr->next = node;
    //        }
    //    }

    auto createTree(int data)
    {

        TreeNode* node = new TreeNode(data);
        return node;
    }

    // Given a binary tree, print its nodes in inorder
    void printInorder(struct TreeNode* node)
    {
        if (node == nullptr) return;
        printInorder(node->left);
        std::cout << node->data << " ";

        printInorder(node->right);
    }
} // namespace apple_detail

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief find sum of three values in a vector which is equal to a specific number
/// \param vec
/// \param sum
/// \return
///
bool isExist(std::vector<int>& vec, int sum)
{
    std::sort(vec.begin(), vec.end());
    for (size_t i = 0; i < vec.size() - 1; ++i)
    {
        int newSum = vec.at(i) + vec.at(i + 1);
        for (size_t j = i + 2; j < vec.size(); ++j)
        {
            if (newSum + vec.at(j) == sum)
            {
                return true;
            }
            if (newSum + vec.at(j) > sum)
            {
                continue;
            }
            else if (newSum + vec.at(j) < sum)
            {
                --i;
            }

            if (i < j) break;
        }
    }
    return false;
}

void testIsExist()
{
    std::vector<int> arr = {-25, -10, -7, -3, 2, 4, 8, 10};

    /*
     *
     *
-3: 1
2: 1
4: 1
8: 1
7: 1
1: 0
     */
    //    std::cout << "-8: " << isExist(arr, -8) << std::endl;
    //    std::cout << "-25: " << isExist(arr, -25) << std::endl;
    //    std::cout << "0: " << isExist(arr, 0) << std::endl;
    //    std::cout << "-42: " << isExist(arr, -42) << std::endl;
    //    std::cout << "22: " << isExist(arr, 22) << std::endl;
    //    std::cout << "-7: " << isExist(arr, -7) << std::endl;
    std::cout << "-3: " << isExist(arr, -3) << std::endl;
    //    std::cout << "2: " << isExist(arr, 2) << std::endl;
    //    std::cout << "4: " << isExist(arr, 4) << std::endl;
    //    std::cout << "8: " << isExist(arr, 8) << std::endl;
    //    std::cout << "7: " << isExist(arr, 7) << std::endl;
    //    std::cout << "1: " << isExist(arr, 1) << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Merge overlapping intervals
/// \param pairs
///
auto mergeIntervals(std::vector<std::pair<int, int>>& pairs)
{
    std::vector<std::pair<int, int>> result{};
    std::pair<int, int> prev;
    for (auto pair : pairs)
    {
        if (result.empty())
        {
            result.push_back(pair);
            prev = pair;
            continue;
        }
        if (prev.second >= pair.first)
        {
            result.pop_back();
            result.push_back({prev.first, pair.second});
            prev = {prev.first, pair.second};
        }
        else
        {
            result.push_back(pair);
            prev = pair;
        }
    }
    return result;
}

void testMergeIntervals()
{
    std::vector<std::pair<int, int>> v{std::pair<int, int>(1, 5),   std::pair<int, int>(3, 7),
                                       std::pair<int, int>(4, 6),   std::pair<int, int>(6, 8),
                                       std::pair<int, int>(10, 12), std::pair<int, int>(11, 15)};

    std::vector<std::pair<int, int>> result = mergeIntervals(v);

    for (int i = 0; i < result.size(); i++)
    {
        std::cout << "[" << result[i].first << ", " << result[i].second << "] ";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Clone a Directed Graph
/// The goal of this exercise is to clone a directed graph and print an output graph using hash
/// table and depth first traversal
///
/// \param pairs

auto addIntegers(apple_detail::ListNode* first, apple_detail::ListNode* second)
{
    apple_detail::ListNode* result;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Determine if two binary trees are identical
/// \param first
/// \param second
/// \return
///
bool visitTreesInorder(apple_detail::TreeNode* first, apple_detail::TreeNode* second)
{
    if (first == nullptr && second == nullptr)
    {
        return true;
    }
    if (first != nullptr && second != nullptr)
    {
        return (
            (first->data == second->data) && visitTreesInorder(first->left, second->left) &&
            visitTreesInorder(first->right, second->right));
    }

    return false;
}

void mirrorBinaryTree(apple_detail::TreeNode* tree)
{
    //    if (tree->left != nullptr)
    //    {
    //        mirrorBinaryTree(tree->left);
    //    }
    //    if (tree->right != nullptr)
    //    {
    //        mirrorBinaryTree(tree->right);
    //    }

    //    apple_detail::TreeNode* temp = tree->left;
    //    tree->left = tree->right;
    //    tree->right = temp;

    if (tree == nullptr) return;
    if (tree->left != nullptr) mirrorBinaryTree(tree->left);
    if (tree->right != nullptr) mirrorBinaryTree(tree->right);
    auto temp = tree->left;
    tree->left = tree->right;
    tree->right = temp;
}

void testMirror()
{
    struct apple_detail::TreeNode* root = apple_detail::createTree(1);
    root->left = apple_detail::createTree(2);
    root->right = apple_detail::createTree(3);
    root->left->left = apple_detail::createTree(4);
    root->left->right = apple_detail::createTree(5);

    apple_detail::printInorder(root);
    mirrorBinaryTree(root);
    apple_detail::printInorder(root);
    delete root;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Find all palindrome substrings
/// \param input
/// \param j
/// \param k
/// \return
///
int findPalindorm(const std::string& input, int j, int k)
{
    int count = 0;
    for (; j >= 0 && k < input.length(); --j, ++k)
    {
        if (input[j] != input[k]) break;
        std::cout << input.substr(j, k - j + 1) << " " << k - j + 1 << std::endl;

        ++count;
    }
    return count;
}

int countNumberOfPalindroms(const std::string& input)
{
    int count = 0;
    for (int i = 0; i < input.length(); ++i)
    {
        count += findPalindorm(input, i - 1, i + 1);
        count += findPalindorm(input, i, i + 1);
    }
    return count;
}
void testPalindolmApple()
{
    using namespace std::string_literals;
    std::cout << countNumberOfPalindroms("sahararahnide");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The goal of this exercise is to reverse the words in a given string. Be sure to note how the words are
/// separated by whitespaces.
/// \param input
///
void reverseWords(std::string input)
{
    std::string result = "";
    size_t pos = 0;
    std::string word;
    while ((pos = input.find(" ")) != std::string::npos)
    {
        word = input.substr(0, pos);
        int n = word.length() - 1;
        for (int i = 0; i < word.length() / 2; i++)
        {
            std::swap(word[i], word[n]);
            n--;
        }
        result = result + word + " ";
        input.erase(0, pos + 1);
    }
    int n = input.length() - 1;
    for (int i = 0; i < input.length() / 2; i++)
    {
        std::swap(input[i], input[n]);
        n--;
    }
    result = result + input;
    std::cout << result;
}

auto largestSumSubArray()
{
    std::vector<int> vec{-4, 2, -5, 1, 2, 3, 6, -5, 1};
    int max = vec.back();
    int maxRes = 0;
    for (auto elem : vec)
    {
        if (elem < 0)
        {
            max = 0;
        }
        if (elem > 0)
        {
            max += elem;
        }
        if (maxRes < max)
        {
            maxRes = max;
        }
    }
    std::cout << maxRes << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The LRUCache class
///
// Time:  O(1), per operation.
// Space: O(k), k is the capacity of cache.
class LRUCache
{
public:
    explicit LRUCache(int capacity) : capa_(capacity) {}

    int get(int key)
    {
        if (map_.find(key) != map_.end())
        {
            // It key exists, update it.
            const auto value = map_[key]->second;
            update(key, value);
            return value;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {
        // If cache is full while inserting, remove the last one.
        if (map_.find(key) == map_.end() && list_.size() == capa_)
        {
            auto del = list_.back();
            list_.pop_back();
            map_.erase(del.first);
        }
        update(key, value);
    }

private:
    std::list<std::pair<int, int>> list_;                                   // key, value
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map_; // key, list iterator
    int capa_;

    // Update (key, iterator of (key, value)) pair
    void update(int key, int value)
    {
        auto it = map_.find(key);
        if (it != map_.end())
        {
            list_.erase(it->second);
        }
        list_.emplace_front(key, value);
        map_[key] = list_.begin();
    }
};

class LFUCache
{
public:
    explicit LFUCache(int capacity) : capacity_(capacity), size_(0), min_freq_(std::numeric_limits<int>::max()) {}
    int get(int key)
    {
        if (!keyToNode_.count(key))
        {
            return -1;
        }
        auto value = std::get<1>(*keyToNode_[key]);
        update(key, value);
        return value;
    }

    void put(int key, int value)
    {
        if (!keyToNode_.count(key) && size_ == capacity_)
        {
            keyToNode_.erase(std::get<0>(freqUsed_[min_freq_].front()));
            freqUsed_[min_freq_].pop_front();
            if (freqUsed_[min_freq_].empty())
            {
                freqUsed_.erase(min_freq_);
            }
            --size_;
        }
        update(key, value);
    }

private:
    size_t capacity_;
    size_t size_;
    int min_freq_;
    std::unordered_map<int, std::list<std::tuple<int, int, int>>> freqUsed_;
    std::map<int, std::list<std::tuple<int, int, int>>::iterator> keyToNode_;

    void update(int key, int value)
    {
        int freq = 0;
        if (keyToNode_.count(key))
        {
            auto old_node = *keyToNode_[key];
            freq = std::get<2>(old_node);
            freqUsed_[freq].erase(keyToNode_[key]);
            if (freqUsed_[freq].empty())
            {
                freqUsed_.erase(freq);
                if (min_freq_ == freq)
                {
                    ++min_freq_;
                }
            }
            --size_;
        }
        min_freq_ = std::min(min_freq_, ++freq);
        freqUsed_[freq].emplace_back(key, value, freq);
        keyToNode_[key] = prev(freqUsed_[freq].end());
        ++size_;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

void testLRU()
{
    LRUCache cache(2);

    cache.put(1, 1);
    assert(cache.get(1) == 1);

    cache.put(2, 2);
    assert(cache.get(2) == 2);

    cache.put(3, 3); // evicts key 1
    assert(cache.get(1) == -1);

    cache.put(2, 4);
    assert(cache.get(2) == 4);

    cache.put(4, 4); // evicts key 3
    assert(cache.get(3) == -1);

    assert(cache.get(5) == -1);
}

//////////////////////////////////////////////////////////////////////////////////////
apple_detail::ListNode* reverseLinkedList(apple_detail::ListNode* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }
    auto next = head->next;
    auto rest = reverseLinkedList(next);
    next->next = head;
    head->next = nullptr;
    return rest;
}

apple_detail::ListNode* reverseLinkedListLoop(apple_detail::ListNode* head)
{
    auto current = head;
    apple_detail::ListNode *prev = nullptr, *next = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The Graph class
///
class Graph
{
    int V_;
    std::vector<std::list<int>> adj_;

public:
    explicit Graph(int V) : V_{V}
    {
        adj_.resize(V_);
    }
    void addEdge(int v, int w)
    {
        adj_.at(v).push_back(w);
    }

    void BFS(int s)
    {
        std::vector<bool> visited;
        visited.resize(V_, false);
        std::list<int> queue;
        visited.at(s) = true;
        queue.push_back(s);
        while (!queue.empty())
        {
            auto elem = queue.front();
            queue.pop_front();
            auto adjs = adj_.at(elem);
            for (auto adj : adjs)
            {
                if (!visited[adj])
                {
                    visited.at(adj) = true;
                    queue.push_back(adj);
                }
            }
        }
    }

    void DFS(int s)
    {
        std::stack<int> stack;
        stack.push(s);
        std::vector<bool> visited;
        visited.resize(V_, false);
        visited.at(s) = true;
        while (!stack.empty())
        {
            auto elem = stack.top();
            stack.pop();
            auto adjs = adj_.at(elem);
            for (auto adj : adjs)
            {
                if (!visited[adj]) stack.push(adj);
            }
        }
    }
};

template<class T>
inline constexpr T pow(const T base, unsigned const exponent)
{
    // (parentheses not required in next line)
    return (exponent == 0)       ? 1
           : (exponent % 2 == 0) ? pow(base, exponent / 2) * pow(base, exponent / 2)
                                 : base * pow(base, (exponent - 1) / 2) * pow(base, (exponent - 1) / 2);
}

apple_detail::ListNode* SamanRevertLink(apple_detail::ListNode* head)
{
    if (head == nullptr || head->next == nullptr) return head;
    auto res = head->next;
    head->next->next = res->next;
    head->next = nullptr;
    return res;
}

void testSaman()
{
    auto head = new apple_detail::ListNode(1);
    head->next = new apple_detail::ListNode(2);
    head->next->next = new apple_detail::ListNode(3);
    head->next->next->next = new apple_detail::ListNode(4);
    auto res = SamanRevertLink(head);
    delete head;
}

bool find2(std::vector<int> vec, int startIndex, int target)
{
    for (int i = startIndex, j = vec.size() - 1; i < j;)
    {
        auto sum = vec[i] + vec[j];
        if (sum == target) return true;
        if (sum > target)
            --j;
        else
            ++i;
    }
    return false;
}
bool is3Numbers(std::vector<int> vec, int target)
{
    std::sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size() - 2; ++i)
    {
        auto remain = target - vec[i];
        if (find2(vec, i + 1, remain)) return true;
    }
    return false;
}

void pushLinkedLinst(apple_detail::ListNode** head, int newData)
{
    auto newNode = new apple_detail::ListNode(newData);
    newNode->next = (*head);
    (*head) = newNode;
}

void insertAfter(apple_detail::ListNode* head, int newData)
{
    auto newNode = new apple_detail::ListNode(newData);
    auto temp = head->next;
    head->next = newNode;
    newNode->next = temp;
}

void insertInMiddleLinkedList(apple_detail::ListNode** head, int newData)
{
    auto newNode = new apple_detail::ListNode(newData);
    auto ptr = *head;
    int len = 0;
    while (ptr != nullptr)
    {
        ++len;
        ptr = ptr->next;
    }

    auto count = len / 2;
    ptr = *head;
    while (count-- > 1)
    {
        ptr = ptr->next;
    }

    newNode->next = ptr->next;
    ptr->next = newNode;
}

void concatenate(apple_detail::ListNode* a, apple_detail::ListNode* b)
{
    if (a != nullptr && b != nullptr)
    {
        if (a->next == nullptr)
            a->next = b;
        else
            concatenate(a->next, b);
    }
}

void sortList(apple_detail::ListNode** head)
{
    auto prev = *head;
    auto current = (*head)->next;
    while (current != nullptr)
    {
        if (current->data < prev->data)
        {
            prev->next = current->next;
            current->next = (*head);
            (*head) = current;
            current = prev;
        }
        else
        {
            prev = current;
        }
        current = current->next;
    }
}

int heightTree(apple_detail::TreeNode* root)
{
    if (root == nullptr) return 0;
    auto left = root->left;
    auto right = root->right;
    auto leftH = heightTree(left) + 1;
    auto rightH = heightTree(right) + 1;
    return leftH > rightH ? leftH : rightH;
}

void levelOrder(apple_detail::TreeNode* root, int level)
{
    if (root == nullptr) return;
    if (level == 1)
        std::cout << root->data << " ";
    else if (level > 1)
    {
        levelOrder(root->left, level - 1);
        levelOrder(root->right, level - 1);
    }
}
void treeLevelOrder(apple_detail::TreeNode* root)
{
    auto h = heightTree(root);
    for (int i = 1; i <= h; i++)
    {
        levelOrder(root, i);
    }
}

template<int N>
struct fibonacci
{
    static constexpr int value = fibonacci<N - 1>::value + fibonacci<N - 2>::value;
};

template<>
struct fibonacci<0>
{
    static constexpr int value = 0;
};
template<>
struct fibonacci<1>
{
    static constexpr int value = 1;
};

void findNumbers(std::vector<int>& ar, int sum, std::vector<std::vector<int>>& res, std::vector<int>& r, int i)
{
    if (sum == 0)
    {
        res.push_back(r);
        return;
    }

    while (i < ar.size() && sum - ar[i] >= 0)
    {
        r.push_back(ar[i]);
        findNumbers(ar, sum - ar[i], res, r, i);
        i++;
        r.pop_back();
    }
}

std::vector<std::vector<int>> findCombination(std::vector<int> vec, int target)
{
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    std::vector<int> r;
    std::vector<std::vector<int>> res;
    findNumbers(vec, target, res, r, 0);
    return res;
}

class LRU
{
public:
    explicit LRU(int size) : capacity_{size} {}

    int get(int key)
    {
        if (map_.find(key) != map_.end())
        {
            auto const value = map_[key]->second;
            update(key, value);
            return value;
        }
        return -1;
    }

    void put(int key, int value)
    {
        if (map_.find(key) == map_.end() && capacity_ == list_.size())
        {
            auto del = list_.back();
            list_.pop_back();
            map_.erase(del.first);
        }
        update(key, value);
    }

private:
    int capacity_;
    using List = std::list<std::pair<int, int>>;
    List list_;
    std::map<int, List::iterator> map_;
    void update(int key, int value)
    {
        auto it = map_.find(key);
        if (it != map_.end())
        {
            list_.erase(it->second);
        }
        list_.emplace_front(key, value);
        map_[key] = list_.begin();
    }
};

class LFU
{
public:
    explicit LFU(size_t capacity) : capacity_{capacity}, size_{0}, min_freq_{std::numeric_limits<int>::max()} {}
    int get(int key)
    {
        if (map_.find(key) != map_.end())
        {
            auto const value = std::get<1>(*map_[key]);
            update(key, value);
        }
        return -1;
    }

    void put(int key, int value)
    {
        if (map_.find(key) == map_.end() && capacity_ == size_)
        {

            map_.erase(std::get<0>(freq[min_freq_].front()));
            freq[min_freq_].pop_front();
            if (freq[min_freq_].empty())
            {
                freq.erase(min_freq_);
            }
            --size_;
        }
        update(key, value);
    }

private:
    size_t capacity_;
    size_t size_;
    int min_freq_;
    using List = std::list<std::tuple<int, int, int>>;
    std::unordered_map<int, List> freq;
    std::map<int, List::iterator> map_;

    void update(int key, int value)
    {
        int frequency = 0;
        if (map_.count(key))
        {
            auto old_node = *map_[key];
            frequency = std::get<2>(old_node);
            freq[frequency].erase(map_[key]);
            if (freq[frequency].empty())
            {
                freq.erase(frequency);
                if (min_freq_ == frequency)
                {
                    ++min_freq_;
                }
            }
            --size_;
        }
        min_freq_ = std::min(min_freq_, ++frequency);
        freq[frequency].emplace_back(key, value, frequency);
        map_[key] = prev(freq[frequency].end());
        ++size_;
    }
};

using Matrix = std::vector<std::vector<int>>;

void print2DArray(Matrix arr)
{
    int n = arr.size();
    for (int a = 0; a < n; a++)
    {
        for (int b = 0; b < n; b++)
        {
            std::cout << arr[a][b] << " ";
        }
        std::cout << std::endl;
    }
}
void rotateMatrixClockWise(Matrix& matrix)
{
    int n = matrix.size();

    print2DArray(matrix);
    //    for (int i = 0; i < n / 2; i++)
    //    {
    //        for (int j = 0; j < n; j++)
    //        {
    //            std::swap(matrix[i][j], matrix[n - i - 1][j]);
    //        }
    //    }
    //    for (int i = 0; i < n; ++i)
    //    {
    //        for (int j = i + 1; j < n; ++j)
    //        {
    //            std::swap(matrix[i][j], matrix[j][i]);
    //        }
    //    }

    for (int i = 0; i < n; i = i + 1)
    {
        for (int j = i; j < n; j = j + 1)
        {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }

    int i = 0, j = 0, column = 0;
    while (column < n)
    {
        i = 0, j = n - 1;
        while (i < j)
        {
            std::swap(matrix[i][column], matrix[j][column]);
            i = i + 1;
            j = j - 1;
        }
        column = column + 1;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    print2DArray(matrix);
}
