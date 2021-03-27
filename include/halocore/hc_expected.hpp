/**
 * MIT License
 *
 * Copyright (c) 2021 Garrett Franks
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#ifndef HC_EXPECTED_HPP
#define HC_EXPECTED_HPP

#include <utility>
#include <stdexcept>

#include "std/hc_type_traits.hpp"
#include "std/hc_concepts.hpp"

namespace hc {

namespace detail {

template<typename T> concept Success_Compatible = std::move_constructible<T> && std::destructible<T>;
template<typename T> concept Error_Compatible   = std::move_constructible<T> && std::destructible<T>;

}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
class expected {
    static constexpr bool is_nothrow_move_constructible = std::is_nothrow_move_constructible_v<Value>
                                                       && std::is_nothrow_move_constructible_v<Error>;
    static constexpr bool is_nothrow_swap = is_nothrow_move_constructible
                                         && std::is_nothrow_swappable_v<Value>
                                         && std::is_nothrow_swappable_v<Error>;
    template<typename... Args>
    static constexpr bool is_value_nothrow_constructible = std::is_nothrow_constructible_v<Value, Args...>;
    template<typename... Args>
    static constexpr bool is_error_nothrow_constructible = std::is_nothrow_constructible_v<Value, Args...>;

public:
    constexpr                 expected(expected const &);
    constexpr                 expected(expected &&) noexcept(is_nothrow_move_constructible);
                              ~expected();

    constexpr Value &         get_value();
    constexpr Error &         get_error();

    constexpr void            swap(expected &) noexcept(is_nothrow_swap);

    template<typename... Args>
    static constexpr expected success(Args &&... args) noexcept(is_value_nothrow_constructible<Args...>);
    template<typename... Args>
    static constexpr expected error(Args &&... args) noexcept(is_error_nothrow_constructible<Args...>);

    constexpr expected &      operator=(expected) noexcept(is_nothrow_swap);

    constexpr                 operator bool() const noexcept;

private:
    constexpr                 expected() {} // cant be publicly initialized in invalid state

    union {
        Value value;
        Error error_value;
    };
    bool      valid;
};

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
constexpr expected<Value, Error>::expected(expected const &e)
    : valid{ e.valid }
{
    if (valid)
        new(&value) Value{ e.value };
    else
        new(&error_value) Error{ e.error_value };
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
constexpr expected<Value, Error>::expected(expected &&e) noexcept(is_nothrow_move_constructible)
    : valid{ e.valid }
{
    if (valid)
        new(&value) Value{ std::move(e.value) };
    else
        new(&error_value) Error{ std::move(e.error_value) };
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
expected<Value, Error>::~expected()
{
    if (valid)
        value.~Value();
    else
        error_value.~Error();
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
constexpr inline Value &expected<Value, Error>::get_value()
{
    if (!valid)
        throw std::logic_error{ "Tried to get an invalid value!" };
    return value;
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
constexpr inline Error &expected<Value, Error>::get_error()
{
    if (valid)
        throw std::logic_error{ "Tried to get an invalid error!" };
    return error_value;
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
constexpr void expected<Value, Error>::swap(expected &e) noexcept(is_nothrow_swap)
{
    if (valid) {
        if (e.valid) {
            std::swap(value, e.value);
        } else {
            auto t = std::move(e.error_value);
            e.err.~Error();
            new(&e.value) Value{ std::move(value) };
            value.~Value();
            new(&error_value) Error{ std::move(t) };
            std::swap(valid, e.valid);
        }
    } else {
        if (e.valid)
            e.swap(*this);
        else
            std::swap(error_value, e.error_value);
    }
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
constexpr inline expected<Value, Error> &expected<Value, Error>::operator=(expected e) noexcept(is_nothrow_swap)
{
    swap(e);
    return *this;
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
template<typename... Args>
constexpr expected<Value, Error> expected<Value, Error>::success(Args &&... args) noexcept(is_value_nothrow_constructible<Args...>)
{
    expected r{};
    r.valid = true;
    new(&r.value) Value{ std::forward<Args>(args)... };
    return r;
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
template<typename... Args>
constexpr expected<Value, Error> expected<Value, Error>::error(Args &&... args) noexcept(is_error_nothrow_constructible<Args...>)
{
    expected r{};
    r.valid = false;
    new(&r.error_value) Error{ std::forward<Args>(args)... };
    return r;
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
constexpr inline expected<Value, Error>::operator bool() const noexcept
{
    return valid;
}

template<detail::Success_Compatible Value, detail::Error_Compatible Error>
constexpr inline void swap(expected<Value, Error> &e1, expected<Value, Error> &e2) noexcept(noexcept(e1.swap(e2)))
{
    e1.swap(e2);
}

}

#endif // HC_EXPECTED_HPP
