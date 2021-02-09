#ifndef HC_SPAN_HPP
#define HC_SPAN_HPP

#if __has_include(<span>)
#    include <span>
#elif __has_include(<experimental/span>)
#    include <experimental/span>

namespace std {
template<typename T>
using span = experimental::span<T>;
}

#else
#    error "can't find span header!"
#endif

#endif // HC_SPAN_HPP
