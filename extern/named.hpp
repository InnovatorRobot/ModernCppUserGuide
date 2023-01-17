#ifndef VAS_ENV_EXT_NAMED_H_
#define VAS_ENV_EXT_NAMED_H_

#include <string_view>
#include <type_traits>

#include "string_literal.hpp"

namespace vas::env::ext
{
    // Concept accepting all named types (regardless of the method used for naming the type)
    template<typename T>
    concept HasName = std::is_convertible_v<decltype(T::name), std::string_view>;

    // Helper to create "strong" typedefs.
    // I.e. 'using Foo = Named<int, "foo">;' will make Foo different from a simple 'int'.
    template<typename T, StringLiteral Name>
    class Named
    {
    public:
        using Type = T;

        constexpr Named() noexcept = default;

        constexpr explicit Named(Type const& value) : value_{value} {}
        constexpr explicit Named(Type&& value) : value_{std::move(value)} {}

        constexpr operator Type&()
        {
            return value_;
        }
        constexpr operator Type const&() const
        {
            return value_;
        }

        static constexpr auto name = Name.value;

    private:
        Type value_;
    };

    template<typename T, StringLiteral Name>
    bool operator<(ext::Named<T, Name> const& first, ext::Named<T, Name> const& second)
    {
        return static_cast<T const&>(first) < static_cast<T const&>(second);
    }

    // Strong type flag checking that a type is exactly Named<T>
    template<typename T>
    struct IsNamed : std::false_type
    {
    };

    template<typename T, StringLiteral Name>
    struct IsNamed<Named<T, Name>> : std::true_type
    {
    };

    template<class T>
    constexpr bool IsNamedV = IsNamed<T>::value;

    template<typename T>
    struct RemoveNamed
    {
        using Type = T;
    };
    template<typename T, StringLiteral Name>
    struct RemoveNamed<Named<T, Name>>
    {
        using Type = T;
    };

    template<typename T>
    using RemoveNamedT = typename RemoveNamed<T>::Type;
} // namespace vas::env::ext

#endif // VAS_ENV_EXT_NAMED_H_
