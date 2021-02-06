#ifndef HC_ALLOCATOR_HPP
#define HC_ALLOCATOR_HPP

#include <cstddef>

#include "hc_def.hpp"
#include "hc_memory_resource.hpp"

namespace hc {

class HC_API allocator : public std::pmr::memory_resource {
public:
    constexpr     allocator() = default;
    constexpr     allocator(allocator const &) = default;

    void *        reallocate(void *ptr, std::size_t bytes, std::size_t alignment);

private:
    virtual void *do_allocate(std::size_t bytes, std::size_t alignment) override;
    virtual void  do_deallocate(void *ptr, std::size_t bytes, std::size_t alignment) override;
    virtual bool  do_is_equal(std::pmr::memory_resource const &mr) const noexcept override;
};

HC_API allocator &get_default_allocator();

}

#endif // HC_ALLOCATOR_HPP
