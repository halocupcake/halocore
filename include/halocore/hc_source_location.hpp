#ifndef HC_SOURCE_LOCATION_HPP
#define HC_SOURCE_LOCATION_HPP

#include "hc_def.hpp"

#if __has_include(<source_location>)
#    include <source_location>
#elif __has_include(<experimental/source_location>)
#    include <experimental/source_location>

namespace std {
using source_location = experimental::source_location;
}

#else
#    define HC_NO_STD_SOURCE_LOCATION
// #    error "can't find source_location header!"
#endif

namespace hc {

struct HC_API source_location { // getting rid of this as soon as there's better source_location support in compilers
public:                         // disclaimer: this may not work with std::source_location, havent tested it yet because msvc sucks
    constexpr               source_location(unsigned long line, char const *file) noexcept;
    constexpr               source_location(source_location const &);
    constexpr               source_location(source_location &&) noexcept;

    constexpr char const *  get_file() const noexcept { return file_; }
    constexpr unsigned long get_line() const noexcept { return line_; }

private:
    unsigned long const line_;
    char const *const   file_;
};

#ifdef HC_NO_STD_SOURCE_LOCATION
#    define HC_SOURCE_LOCATION_CURRENT \
         source_location{ __LINE__, __FILE__ }
#else
#    define HC_SOURCE_LOCATION_CURRENT \
         source_location{ std::source_location::current().line(), std::source_location::current().file_name() }
#endif

constexpr source_location::source_location(unsigned long line, char const *const file) noexcept
    : line_{ line }
    , file_{ file }
{}

constexpr source_location::source_location(source_location const &sl)
    : line_{ sl.line_ }
    , file_{ sl.file_ }
{}

constexpr source_location::source_location(source_location &&sl) noexcept
    : line_{ sl.line_ }
    , file_{ sl.file_ }
{}

}

#endif // HC_SOURCE_LOCATION_HPP
