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

#ifndef HC_CSTR_HPP
#define HC_CSTR_HPP

#include <memory>

#include "std/hc_concepts.hpp"
#include "std/hc_type_traits.hpp"

namespace hc {

namespace detail {

template<typename T>
concept std_string = requires(T t) {
        { t.c_str() } noexcept -> std::convertible_to<char const *>;
    };

}



constexpr char *      get_cstr(char *) noexcept;
constexpr char const *get_cstr(char const *) noexcept;
constexpr char const *get_cstr(detail::std_string auto const &) noexcept;

template<typename T>
concept mutable_cstr = requires(T t) {
        { get_cstr(t) } -> std::same_as<char *>;
    };

template<typename T>
concept immutable_cstr = requires(T t) {
        { get_cstr(t) } -> std::convertible_to<char const *>;
    };



constexpr inline char *get_cstr(char *const s) noexcept
{
    return s;
}

constexpr inline char const *get_cstr(char const *const s) noexcept
{
    return s;
}

constexpr inline char const *get_cstr(detail::std_string auto const &s) noexcept
{
    return s.c_str();
}

}

#endif // HC_CSTR_HPP
