#ifndef STRINGANDREGULAREXPERISSIONS_HPP
#define STRINGANDREGULAREXPERISSIONS_HPP
#include <iostream>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cassert>
template<typename Iter>
auto binaryToString(Iter begin, Iter end, bool const uppercase = false)
{
    std::stringstream sss;
    if (uppercase)
    {
        sss.setf(std::ios_base::uppercase);
    }
    for (; begin != end; ++begin)
    {
        sss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*begin);
    }
    return sss.str();
}

void testBinaryToString()
{
    std::vector<unsigned char> v{0xBA, 0xAD, 0xF0, 0x0D};
    std::cout << binaryToString(v.begin(), v.end()) << "\n";
}

unsigned char hexchar_to_int(char const ch)
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    throw std::invalid_argument("Invalid hexadecimal character");
}
std::vector<unsigned char> hexstr_to_bytes(std::string_view str)
{
    std::vector<unsigned char> result;
    for (size_t i = 0; i < str.size(); i += 2)
    {
        result.push_back((hexchar_to_int(str[i]) << 4) | hexchar_to_int(str[i + 1]));
    }
    return result;
}

/// Capitalizing an article title

template<class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template<class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

///////////////////////////////////////////////
/// \brief capitalize
/// \param text
/// \return
///
template<class Elem>
tstring<Elem> capitalize(tstring<Elem> const& text)
{
    tstringstream<Elem> result;
    bool newWord = true;
    for (auto const ch : text)
    {
        newWord = newWord || std::isspace(ch) || std::ispunct(ch);
        if (std::isalpha(ch))
        {
            if (newWord)
            {
                result << static_cast<Elem>(std::toupper(ch));
                newWord = false;
            }
            else
            {
                result << static_cast<Elem>(std::tolower(ch));
            }
        }
        else
        {
            result << ch;
        }
    }
    return result.str();
}

void testCapitalize()
{
    using namespace std::string_literals;
    assert("The C++ Challenger"s == capitalize("the c++ challenger"s));
    assert("This Is An Example, Should Work!"s == capitalize("THIS IS an ExamplE, should wORk!"s));
}

///////////////////////////////////////////////
/// \brief joinStrings
/// \param begin
/// \param end
/// \param separator
/// \return
///
template<typename Iter>
std::string joinStrings(Iter begin, Iter end, char const* const separator)
{
    std::ostringstream os;
    std::copy(begin, end - 1, std::ostream_iterator<std::string>(os, separator));
    os << *(end - 1);
    return os.str();
}

template<typename C>
std::string joinStrings(C const& c, char const* const separator)
{
    if (c.size() == 0) return std::string{};
    return joinStrings(std::begin(c), std::end(c), separator);
}
void testJoinString()
{
    using namespace std::string_literals;
    std::vector<std::string> v1{"this", "is", "an", "example"};
    std::vector<std::string> v2{"example"};
    std::vector<std::string> v3{};
    assert(joinStrings(v1, " ") == "this is an example"s);
    assert(joinStrings(v2, " ") == "example"s);
    assert(joinStrings(v3, " ") == ""s);
}

//////////////////////////////////////////
/// \brief longestPalindrome
/// \param str
/// \return
///
std::string longestPalindrome(std::string_view str)
{
    auto const len = str.size();
    size_t longestBegin = 0;
    size_t maxLen = 1;
    std::vector<bool> table(len * len, false);

    for (auto i = 0; i < len; ++i)
    {
        table[len * i + i] = true;
    }
    for (size_t i = 0; i < len - 1; i++)
    {
        if (str[i] == str[i + 1])
        {
            table[i * len + i + 1] = true;
            if (maxLen < 2)
            {
                longestBegin = i;
                maxLen = 2;
            }
        }
    }
    for (size_t k = 3; k <= len; k++)
    {
        for (size_t i = 0; i < len - k + 1; i++)
        {
            size_t j = i + k - 1;
            if (str[i] == str[j] && table[(i + 1) * len + j - 1])
            {
                table[i * len + j] = true;
                if (maxLen < k)
                {
                    longestBegin = i;
                    maxLen = k;
                }
            }
        }
    }
    return std::string(str.substr(longestBegin, maxLen));
}

void testPalindolme()
{
    using namespace std::string_literals;
    assert(longestPalindrome("sahararahnide") == "hararah");
    assert(longestPalindrome("level") == "level");
    assert(longestPalindrome("s") == "s");
}

#endif // STRINGANDREGULAREXPERISSIONS_HPP
