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

#ifndef HC_UTILITY_HPP
#define HC_UTILITY_HPP

#if __has_include(<utility>)
#    include <utility>
#elif __has_include(<experimental/utility>)
#    include <experimental/utility>
#else
#    error "can't find utility header!"
#endif

#include "type_traits"

namespace hc {

template<typename Enumerator>
constexpr std::underlying_type_t<Enumerator> to_underlying(Enumerator v) noexcept;



template<typename Enumerator>
constexpr inline std::underlying_type_t<Enumerator> to_underlying(Enumerator const v) noexcept
{
    return static_cast<std::underlying_type_t<Enumerator>>(v);
}

}

#endif // HC_UTILITY_HPP
