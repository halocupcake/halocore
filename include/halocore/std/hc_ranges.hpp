#ifndef HC_RANGES_HPP
#define HC_RANGES_HPP

#if __has_include(<ranges>)
#    include <ranges>
#elif __has_include(<experimental/ranges>)
#    include <experimental/ranges>
#else
#    error "can't find ranges header!"
#endif

#endif // HC_RANGES_HPP
