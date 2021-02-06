#include <halocore/hc_allocator.hpp>

#include <halocore/hc_memory.hpp>

namespace hc {

void *allocator::do_allocate(std::size_t bytes, std::size_t alignment)
{
    return allocate_aligned(bytes, alignment);
}

void *allocator::reallocate(void *const ptr, std::size_t bytes, std::size_t alignment)
{
    return reallocate_aligned(ptr, bytes, alignment);
}

void allocator::do_deallocate(void *const ptr, std::size_t bytes, std::size_t alignment)
{
    free_aligned(ptr);
}

bool allocator::do_is_equal(std::pmr::memory_resource const &mr) const noexcept
{
    return this == &mr;
}

allocator &get_default_allocator()
{
    static allocator da{};
    return da;
}

}
