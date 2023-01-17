#ifndef VAS_ENV_EXT_STRING_LITERAL_H_
#define VAS_ENV_EXT_STRING_LITERAL_H_

#include <algorithm>

namespace vas::env::ext
{
    template<std::size_t N>
    struct StringLiteral
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init, cppcoreguidelines-avoid-c-arrays)
        constexpr StringLiteral(char const (&str)[N])
        {
            std::copy_n(str, N, value);
        }

        constexpr operator std::string_view() const
        {
            return {value};
        }

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
        char value[N];
    };

    template<std::size_t N, std::size_t M>
    constexpr auto operator+(StringLiteral<N> const& first, StringLiteral<M> const& second)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
        char cat[N + M - 1]{};
        std::copy_n(first.value, N - 1, cat);
        std::copy_n(second.value, M, &cat[N - 1]);
        return StringLiteral<N + M - 1>{cat};
    }

    template<std::size_t N, std::size_t M>
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
    constexpr auto operator+(StringLiteral<N> const& first, char const (&second)[M])
    {
        return first + StringLiteral<M>{second};
    }

    template<std::size_t N, std::size_t M>
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
    constexpr auto operator+(char const (&first)[N], StringLiteral<M> const& second)
    {
        return StringLiteral<N>{first} + second;
    }

} // namespace vas::env::ext

#endif // VAS_ENV_EXT_STRING_LITERAL_H_
