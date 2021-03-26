#ifndef HC_COMPARE_HPP
#define HC_COMPARE_HPP

#if __has_include(<compare>)
#    include <compare>
#elif __has_include(<experimental/compare>)
#    include <experimental/compare>
#else
#    error "can't find compare header!"
#endif

#endif // HC_COMPARE_HPP
