#ifndef HC_BITFLAGS_HPP
#define HC_BITFLAGS_HPP

#include "std/hc_type_traits.hpp"
#include "std/hc_concepts.hpp"
#include "std/hc_compare.hpp"

namespace hc {

template<typename T>
concept Bitflag_Compatible = is_scoped_enum_v<T> && std::unsigned_integral<std::underlying_type_t<T>>;

// type-safe bitflag for scoped enums
template<Bitflag_Compatible T>
class bitflags {
public:
    using mask_type = std::underlying_type_t<T>;

             constexpr        bitflags() noexcept;
             constexpr        bitflags(T bit) noexcept;
    explicit constexpr        bitflags(mask_type mask) noexcept;

    constexpr bitflags &      operator&=(bitflags bf) noexcept;
    constexpr bitflags &      operator|=(bitflags bf) noexcept;
    constexpr bitflags &      operator^=(bitflags bf) noexcept;
    constexpr bitflags &      operator&=(T bf) noexcept;
    constexpr bitflags &      operator|=(T bf) noexcept;
    constexpr bitflags &      operator^=(T bf) noexcept;

    friend constexpr bitflags operator&(bitflags a, bitflags b) noexcept { return bitflags<T>{ a } &= b; }
    friend constexpr bitflags operator|(bitflags a, bitflags b) noexcept { return bitflags<T>{ a } |= b; }
    friend constexpr bitflags operator^(bitflags a, bitflags b) noexcept { return bitflags<T>{ a } ^= b; }
    friend constexpr bitflags operator&(bitflags a, T b) noexcept        { return bitflags<T>{ a } &= b; }
    friend constexpr bitflags operator|(bitflags a, T b) noexcept        { return bitflags<T>{ a } |= b; }
    friend constexpr bitflags operator^(bitflags a, T b) noexcept        { return bitflags<T>{ a } ^= b; }

    constexpr bool            operator!() const noexcept;

    constexpr auto            operator<=>(bitflags const &) const noexcept = default;

    explicit constexpr        operator bool() const noexcept;
    explicit constexpr        operator mask_type() const noexcept;

private:
    mask_type mask_;
};

template<Bitflag_Compatible T>
inline constexpr bitflags<T>::bitflags() noexcept
    : mask_{ 0u }
{}

template<Bitflag_Compatible T>
inline constexpr bitflags<T>::bitflags(T bit) noexcept
    : mask_{ static_cast<mask_type>(bit) }
{}

template<Bitflag_Compatible T>
inline constexpr bitflags<T>::bitflags(mask_type mask) noexcept
    : mask_{ mask }
{}

template<Bitflag_Compatible T>
inline bitflags<T> constexpr &bitflags<T>::operator&=(bitflags bf) noexcept
{
    mask_ &= bf.mask_;
    return *this;
}

template<Bitflag_Compatible T>
inline bitflags<T> constexpr &bitflags<T>::operator|=(bitflags bf) noexcept
{
    mask_ |= bf.mask_;
    return *this;
}

template<Bitflag_Compatible T>
inline bitflags<T> constexpr &bitflags<T>::operator^=(bitflags bf) noexcept
{
    mask_ ^= bf.mask_;
    return *this;
}

template<Bitflag_Compatible T>
inline bitflags<T> constexpr &bitflags<T>::operator&=(T bf) noexcept
{
    mask_ &= static_cast<mask_type>(bf);
    return *this;
}

template<Bitflag_Compatible T>
inline bitflags<T> constexpr &bitflags<T>::operator|=(T bf) noexcept
{
    mask_ |= static_cast<mask_type>(bf);
    return *this;
}

template<Bitflag_Compatible T>
inline bitflags<T> constexpr &bitflags<T>::operator^=(T bf) noexcept
{
    mask_ ^= static_cast<mask_type>(bf);
    return *this;
}

template<Bitflag_Compatible T> inline constexpr bool bitflags<T>::operator!() const noexcept          { return !mask_; }
template<Bitflag_Compatible T> inline constexpr      bitflags<T>::operator bool() const noexcept      { return !!mask_; }
template<Bitflag_Compatible T> inline constexpr      bitflags<T>::operator mask_type() const noexcept { return mask_; }

}

#endif // HC_BITFLAGS_HPP
