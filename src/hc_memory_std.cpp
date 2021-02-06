#include <halocore/hc_memory.hpp>

#include <cstdlib>

#include <new>

namespace hc {

void *allocate_aligned(std::size_t size, std::size_t alignment)
{
    void *const ptr = std::aligned_alloc(alignment, size);
    if (!ptr)
        throw std::bad_alloc{};
    return ptr;
}

void *reallocate_aligned(void *ptr, std::size_t size, std::size_t alignment)
{
    ptr = std::realloc(ptr, size);
    if (!ptr)
        throw std::bad_alloc{};
    return ptr;
}

void free_aligned(void *const ptr) noexcept
{
    std::free(ptr);
}

}
