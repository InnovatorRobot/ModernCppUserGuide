#ifndef VAS_ENV_EXT_IS_OPTIONAL_H_
#define VAS_ENV_EXT_IS_OPTIONAL_H_

#include <optional>
#include <type_traits>

namespace vas::env::ext
{
    template<typename T>
    struct IsOptional : std::false_type
    {
    };

    template<typename T>
    struct IsOptional<std::optional<T>> : std::true_type
    {
    };

    template<typename T>
    constexpr bool IsOptionalV = IsOptional<T>::value;
} // namespace vas::env::ext

#endif // VAS_ENV_EXT_IS_OPTIONAL_H_
