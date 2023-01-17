#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H
#include <iostream>
#include <memory>
#include <cerrno>

void testSmartPointer1()
{
    std::unique_ptr<int> uint1 = std::make_unique<int>(1);

    uint1.reset(); // release memory and sets to nullptr
}

void do_something_with_unique_ptr_by_value(std::unique_ptr<int> arg) // you can not pass by value!
{
    std::cout << *arg << "\n";
}

void do_something_with_unique_ptr_by_ref(const std::unique_ptr<int>& arg)
{
    std::cout << *arg << "\n";
}

auto getUniquePtr()
{
    std::unique_ptr<int> res = std::make_unique<int>(2);
    std::cout << "Inner unique_ptr addr is: " << &res << "\n";
    return res; // compiler magic!
}

void testAboveFunction()
{
    std::unique_ptr<int> uint1 = std::make_unique<int>(1);
    //    do_something_with_unique_ptr_by_value(uint1); // compile error!
    do_something_with_unique_ptr_by_value(std::make_unique<int>(1));
    do_something_with_unique_ptr_by_value(std::move(uint1));

    do_something_with_unique_ptr_by_ref(uint1);

    auto uniquePtr = getUniquePtr();
    std::cout << "Outer unique_ptr addr is: " << &uniquePtr << "\n";
}

/// UniquePtr in Array
///
// std::unique_ptr<int[]> uniquePtrArray = std::make_unique<int[3]>({1, 2, 3}); // error!
auto uniquePtrArray = std::unique_ptr<int[]>(new int[3]{1, 2, 3});
auto uniquePtrArray2 = std::make_unique<int[]>(3); // make 3 int: array

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
/// SharedPtr

void testSharedPtr1()
{
    auto sharedPtr1 = std::make_shared<int>(1);
    auto sharedPtr2 = sharedPtr1; // copying is valid here! the counter will be increased!
    std::cout << sharedPtr2.use_count();
}

void convertUniqueToShared()
{
    std::shared_ptr<int> shared;
    auto unique = std::make_unique<int>(1);
    shared = std::move(unique);
    ///
    /// can not assign shared to unique!
    std::unique_ptr<int> unique2;
    std::shared_ptr<int> shared2;
    // unique2 = shared2; compile error!
    shared2 = getUniquePtr();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///
/// WeakPtr
/// For the weak pointer we can not get access to * or ->. it means for getting access we have convert the weakPtr to sharedPtr

void testWeakPtr()
{
    auto sharedPtr1 = std::make_shared<int>(2);
    auto sharedPtr2 = std::make_shared<int>(3);

    std::weak_ptr<int> weakPtr1(sharedPtr1);
    std::weak_ptr<int> weakPtr2(sharedPtr2);

    std::shared_ptr<int> weakTurnedShared = weakPtr1.lock();
    std::cout << weakTurnedShared.use_count() << *weakTurnedShared;
}
#endif // SMARTPOINTERS_H
