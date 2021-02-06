#ifndef HC_HASH_HPP
#define HC_HASH_HPP

#include <cstddef>
#include <cstdint>

namespace hc {

namespace detail {

template<typename T, T prime, T offset>
constexpr auto fnv1a(std::uint8_t const *bytes, std::size_t size) noexcept;

template<typename T, T prime, T offset>
constexpr auto fnv1a(std::uint8_t const *const bytes, std::size_t size) noexcept
{
    T hash = offset;

    for (std::size_t i = 0; i < size; i++) {
        hash ^= bytes[i];
        hash *= prime;
    }

    return hash;
}

}

constexpr std::uint32_t fnv1a_32(std::uint8_t const *bytes, std::size_t size) noexcept;
constexpr std::uint64_t fnv1a_64(std::uint8_t const *bytes, std::size_t size) noexcept;

constexpr std::uint32_t fnv1a_32(std::uint8_t const *const bytes, std::size_t size) noexcept
{
    return detail::fnv1a<std::uint32_t, 0x01000193, 0x811c9dc5>(bytes, size);
}

constexpr std::uint64_t fnv1a_64(std::uint8_t const *const bytes, std::size_t size) noexcept
{
    return detail::fnv1a<std::uint64_t, 0x00000100000001b3, 0xcbf29ce484222325>(bytes, size);
}

}

#endif // HC_HASH_HPP
