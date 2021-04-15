#ifndef HC_ALLOCATOR_HPP
#define HC_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>

#include <array>
#include <string_view>
#include <string>
#include <unordered_map>

#include "std/hc_memory_resource.hpp"
#include "std/hc_type_traits.hpp"
#include "std/hc_source_location.hpp"
#include "hc_def.hpp"

namespace hc {

class HC_API memory_context : public std::pmr::memory_resource {
public:
                  memory_context() = default;
                  memory_context(memory_context const &) = default;

    void *        reallocate(void *ptr, std::size_t bytes, std::size_t alignment = alignof(std::max_align_t));

private:
    virtual void *do_allocate(std::size_t bytes, std::size_t alignment) override;
    virtual void *do_reallocate(void *ptr, std::size_t bytes, std::size_t alignment);
    virtual void  do_deallocate(void *ptr, std::size_t bytes, std::size_t alignment) override;
    virtual bool  do_is_equal(std::pmr::memory_resource const &mr) const noexcept override;
};

struct memory_info {
//    static constexpr std::size_t max_name_length = 64;
//    using name = std::array<char, max_name_length>;

    void *        address;
    std::size_t   size;
    std::size_t   alignment;
    std::size_t   reallocation_count;
//    name          file;
//    name          function;
//    unsigned long line;
//    unsigned long column;
};

static_assert(std::is_standard_layout_v<memory_info>, "ouh i donr goofef");

class HC_API debug_memory_context : public memory_context { // pretty slow, but ill be able to track memory leaks easier
public:                                                     // on debug builds
    using memory_info_map = std::unordered_map<void *, memory_info>;

                           debug_memory_context(std::string_view identifier, source_location const sl = HC_SOURCE_LOCATION_CURRENT);
                           debug_memory_context(debug_memory_context const &);
    virtual                ~debug_memory_context();

    std::string_view       get_identifier() const;
    memory_info_map const &get_memory_info_map() const noexcept;

private:
    virtual void *         do_allocate(std::size_t bytes, std::size_t alignment) override;
    virtual void *         do_reallocate(void *ptr, std::size_t bytes, std::size_t alignment) override;
    virtual void           do_deallocate(void *ptr, std::size_t bytes, std::size_t alignment) override;
    virtual bool           do_is_equal(std::pmr::memory_resource const &mr) const noexcept override;

    std::string     identifier_;
    source_location source_location_;
    memory_info_map memory_infos_;
    bool            is_missing_memory_info_;
    std::uint64_t   total_allocation_count_; // including reallocations
    std::uint64_t   bytes_allocated_;
    std::uint64_t   bytes_deallocated_;
};

inline std::string_view                             debug_memory_context::get_identifier() const               { return identifier_; }
inline debug_memory_context::memory_info_map const &debug_memory_context::get_memory_info_map() const noexcept { return memory_infos_; }

// https://people.cs.umass.edu/~emery/pubs/berger-pldi2001.pdf
class HC_API scoped_allocator {
public:
    scoped_allocator();
    scoped_allocator(memory_context *ctx);

private:

};

template<typename T>
class HC_API pool_allocator {

};

class HC_API free_list_allocator {

};

}

#endif // HC_ALLOCATOR_HPP
