#include <halocore/hc_memory.hpp>

#include <cstdlib>

#include <new>

namespace hc {

void *allocate(std::size_t size)
{
    void *const ptr = std::malloc(size);
    if (!ptr)
        throw std::bad_alloc{};
    return ptr;
}

void *reallocate(void *ptr, std::size_t size)
{
    ptr = std::realloc(ptr, size);
    if (!ptr)
        throw std::bad_alloc{};
    return ptr;
}

void free(void *const ptr) noexcept
{
    std::free(ptr);
}

}

