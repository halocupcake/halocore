#ifndef HC_CONCEPTS_HPP
#define HC_CONCEPTS_HPP

#if __has_include(<concepts>)
#    include <concepts>
#elif __has_include(<experimental/concepts>)
#    include <experimental/concepts>
#else
#    error "can't find concepts header!"
#endif

namespace hc {



}

#endif // HC_CONCEPTS_HPP
