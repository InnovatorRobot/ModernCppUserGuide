#ifndef LANGUAGEFEATURES_HPP
#define LANGUAGEFEATURES_HPP

#include <iostream>
#include <algorithm>
#include <sstream>
/// 1) IPv4 data type
///
///
/// 2) Enumerating IPv4 addresses in a range
///
///
///
class IPV4
{
public:
    constexpr IPV4() : address_{{0}} {}
    constexpr IPV4(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : address_{a, b, c, d} {}
    explicit constexpr IPV4(uint32_t addr)
        : address_{
              static_cast<uint8_t>((addr >> 24) & 0xFF), static_cast<uint8_t>((addr >> 16) & 0xFF),
              static_cast<uint8_t>((addr >> 8) & 0xFF), static_cast<uint8_t>(addr & 0xFF)}
    {
    }

    IPV4(IPV4 const& other) noexcept : address_{other.address_} {}

    IPV4& operator=(IPV4 const& other)
    {
        address_ = other.address_;
        return *this;
    }

    auto toString() const
    {
        std::stringstream sstr;
        sstr << this;
        return sstr.str();
    }

    auto toULong() const
    {
        return (static_cast<unsigned long>(address_[0]) << 24) | (static_cast<unsigned long>(address_[1]) << 16) |
               (static_cast<unsigned long>(address_[2]) << 8) | static_cast<unsigned long>(address_[3]);
    }

    friend std::ostream& operator<<(std::ostream& out, const IPV4& ipv4)
    {
        out << static_cast<int>(ipv4.address_[0]) << '.' << static_cast<int>(ipv4.address_[1]) << '.'
            << static_cast<int>(ipv4.address_[2]) << '.' << static_cast<int>(ipv4.address_[3]);
        return out;
    }

    friend std::istream& operator>>(std::istream& is, IPV4& a)
    {
        char d1, d2, d3;
        int b1, b2, b3, b4;
        is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
        if (d1 == '.' && d2 == '.' && d3 == '.')
            a = IPV4(b1, b2, b3, b4);
        else
            is.setstate(std::ios_base::failbit);
        return is;
    }

    IPV4& operator++()
    {
        *this = IPV4(1 + toULong());
        return *this;
    }

    IPV4& operator++(int)
    {
        IPV4 result(*this);
        ++(*this);
        return *this;
    }

    bool operator==(const IPV4& other) noexcept
    {
        return address_ == other.address_;
    }

    bool operator!=(const IPV4& other) noexcept
    {
        return !(address_ == other.address_);
    }

    bool operator<(IPV4 const& other)
    {
        return toULong() < other.toULong();
    }

    bool operator>(IPV4 const& other)
    {
        return toULong() > other.toULong();
    }

    bool operator>=(IPV4 const& other)
    {
        return !(toULong() < other.toULong());
    }

    bool operator<=(IPV4 const& other)
    {
        return !(toULong() > other.toULong());
    }

private:
    std::array<uint8_t, 4> address_;
};

void testIPV41()
{
    IPV4 address(168, 192, 0, 1);
    std::cout << address << std::endl;
    IPV4 ip;
    std::cout << ip << std::endl;
    std::cin >> ip;
    if (!std::cin.fail()) std::cout << ip << std::endl;
}

void testIPV42()
{
    std::cout << "input range: ";
    IPV4 a1, a2;
    std::cin >> a1 >> a2;
    if (a2 > a1)
    {
        for (IPV4 a = a1; a <= a2; a++)
        {
            std::cout << a << std::endl;
        }
    }
    else
    {
        std::cerr << "invalid range!" << std::endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
/// \brief The array2d class
///

template<typename T, size_t R, size_t C>
class array2d
{
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = value_type const*;

public:
    array2d() : data_(R * C) {}
    explicit array2d(std::initializer_list<T> l) : data_(l) {}

    constexpr T* data() noexcept
    {
        return data_.data();
    }

    constexpr T const* data() const noexcept
    {
        return data_.data();
    }

    constexpr T& at(size_t const r, size_t const c)
    {
        return data_.at(r * C + c);
    }

    constexpr T const& at(size_t const r, size_t const c) const
    {
        return data_.at(r * C + c);
    }

    constexpr T& operator()(size_t const r, size_t const c)
    {
        return data_.at(r * C + c);
    }

    constexpr T const& operator()(size_t const r, size_t const c) const
    {
        return data_.at(r * C + c);
    }

    void fill(T const& value)
    {
        std::fill(std::begin(data_), std::end(data_), value);
    }

    void swap(array2d& other) noexcept
    {
        data_.swap(other.arr);
    }

    const_iterator begin() const
    {
        return data_.data();
    }
    const_iterator end() const
    {
        return data_.data() + data_.size();
    }
    iterator begin()
    {
        return data_.data();
    }
    iterator end()
    {
        return data_.data() + data_.size();
    }

private:
    std::vector<T> data_;
};

////////////////////////////////////////////////////////////////
/// \brief Minimum function with any number of arguments
/// \param first
/// \param args
///
template<typename T, typename... Ts>
auto findMin(T first, Ts... args)
{
    static_assert((std::is_same_v<T, Ts> && ...));
    auto min = first;
    (
        [&]()
        {
            if (min > args)
            {
                min = args;
            }
        }(),
        ...);
    return min;
}

////////////////////////////////////////////////////////////////
/// \brief Adding a range of values to a container
/// \param container
/// \param args
///
template<typename Container, typename... Args>
void push_back(Container& container, Args&&... args)
{
    (container.push_back(args), ...);
}

#endif // LANGUAGEFEATURES_HPP
