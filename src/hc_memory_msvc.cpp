#include <halocore/hc_memory.hpp>

#include <malloc.h>

#include <new>

namespace hc {

void *allocate_aligned(std::size_t size, std::size_t alignment)
{
    void *const ptr = _aligned_malloc(size, alignment);
    if (!ptr)
        throw std::bad_alloc{};
    return ptr;
}

void *reallocate_aligned(void *ptr, std::size_t size, std::size_t alignment)
{
    ptr = _aligned_realloc(ptr, size, alignment);
    if (!ptr)
        throw std::bad_alloc{};
    return ptr;
}

void free_aligned(void *const ptr) noexcept
{
    _aligned_free(ptr);
}

}
