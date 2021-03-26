#ifndef HC_TYPE_TRAITS_HPP
#define HC_TYPE_TRAITS_HPP

#if __has_include(<type_traits>)
#    include <type_traits>
#elif __has_include(<experimental/type_traits>)
#    include <experimental/type_traits>
#else
#    error "can't find type_traits header!"
#endif

namespace hc {

template<typename T> struct is_scoped_enum : std::false_type {};

template<typename T> requires std::is_enum_v<T>
struct is_scoped_enum<T> : std::bool_constant<!std::is_convertible_v<T, std::underlying_type_t<T>>>
{};

template<typename T>
inline constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;

}

#endif // HC_TYPE_TRAITS_HPP
