#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <bitset>
#include <random>
#include <functional>
#include <algorithm>

/// 1)
auto sumNaturalDivisibleBy3and5(int limit)
{
    auto sum = 0;
    while (limit > 0)
    {
        if (limit % 3 == 0 || limit % 5 == 0) sum = sum + limit;
        limit--;
    }
    return sum;
}

/// 2)
uint32_t greatestCommonDivisor(uint32_t const a, uint32_t const b)
{
    return b == 0 ? b : greatestCommonDivisor(b, a % b);
}

/// 3)
uint32_t leastCommonMultiple(uint32_t const a, uint32_t const b)
{
    auto gcd = greatestCommonDivisor(a, b);
    return gcd == 0 ? 0 : (a * (b / gcd));
}

/// To compute lcm for more that two inputs you can use std::accumulate function in numerics header file!
template<class InputIter>
int lcmr(InputIter first, InputIter last)
{
    return std::accumulate(first, last, 1, leastCommonMultiple);
}

/// 4)
auto isPrime(int const num)
{
    if (num <= 3)
    {
        return num > 1;
    }
    else if (num % 2 == 0 || num % 3 == 0)
    {
        return false;
    }
    else
    {
        for (int i = 5; i * i <= num; i += 6)
        {
            if (num % i == 0 || num % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }
}

/// 6) Abundant numbers

void abundantNumber(int limit)
{
    auto sumProperDivisor = [](int number)
    {
        int result = 1;
        for (int i = 2; i <= std::sqrt(number); ++i)
        {
            if (number % i == 0)
            {
                result += (i == (number / i)) ? i : (i + number / i);
            }
        }
        return result;
    };

    for (int i = 10; i <= limit; ++i)
    {
        auto sum = sumProperDivisor(i);
        if (sum > i)
        {
            std::cout << i << ", abundance=" << sum - i << "\n";
        }
    }
}

/// 7) Armstrong numbers
/// An Armstrong number (named so after Michael F. Armstrong), also called a narcissistic
///    number, a pluperfect digital invariant, or a plus perfect number, is a number that is equal to
///    the sum of its own digits when they are raised to the power of the number of digit

/// 8)
std::string to_binary(unsigned int value, int const digits)
{
    return std::bitset<32>(value).to_string().substr(32 - digits, digits);
}

/// 9) Computing the value of Pi

/*
 *
 *
 *
    A suitable solution for approximately determining the value of Pi is using a Monte Carlo
    simulation. This is a method that uses random samples of inputs to explore the behavior of
    complex processes or systems. The method is used in a large variety of applications and
    domains, including physics, engineering, computing, finance, business, and others.
    To do this we will rely on the following idea: the area of a circle with diameter d is PI *
    d^2 / 4. The area of a square that has the length of its sides equal to d is d^2. If we divide
    the two we get PI/4. If we put the circle inside the square and generate random numbers
    uniformly distributed within the square, then the count of numbers in the circle should be
    directly proportional to the circle area, and the count of numbers inside the square should
    be directly proportional to the square’s area. That means that dividing the total number of
    hits in the square and circle should give PI/4. The more points generated, the more
    accurate the result shall be.
    For generating pseudo-random numbers we will use a Mersenne twister and a uniform
    statistical distribution:
 *
 *
 *
 *
 */
template<typename E = std::mt19937, typename D = std::uniform_real_distribution<>>
double computePI(E& engine, D& dist, int const samples = 100000)
{

    auto hit = 0;
    for (auto i = 0; i < samples; ++i)
    {
        auto x = dist(engine);
        auto y = dist(engine);
        if (y <= std::sqrt(1 - std::pow(x, 2)))
        {
            hit += 1;
        }
    }
    return 4.0 * hit / samples;
}
void printPI()
{
    std::random_device rd;
    auto seedData = std::array<int, std::mt19937::state_size>{};
    std::generate(std::begin(seedData), std::end(seedData), std::ref(rd));
    std::seed_seq seq(std::begin(seedData), std::end(seedData));

    auto eng = std::mt19937{seq};
    auto distribution = std::uniform_real_distribution<>{0, 1};
    for (auto j = 0; j < 10; j++)
        std::cout << computePI(eng, distribution) << std::endl;
}

/// 10) validatin ISBNs
/*
The International Standard Book Number (ISBN) is a unique numeric identifier for books.
Currently, a 13-digit format is used. However, for this problem, you are to validate the
former format that used 10 digits. The last of the 10 digits is a checksum. This digit is
chosen so that the sum of all the ten digits, each multiplied by its (integer) weight,
descending from 10 to 1, is a multiple of 11
*/

auto validateISBNS10(std::string_view isbn)
{
    auto valid{false};
    if (isbn.size() == 10 && std::count_if(std::begin(isbn), std::end(isbn), isdigit) == 10)
    {
        auto w{10};
        auto sum = std::accumulate(
            std::begin(isbn), std::end(isbn), 0,
            [&w](int const total, char const c) { return total + w-- * (c * '0'); });
        valid = !(sum % 11);
    }
    return valid;
}
