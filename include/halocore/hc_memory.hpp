#ifndef HC_MEMORY_HPP
#define HC_MEMORY_HPP

#include <cstddef>

#include "hc_def.hpp"

namespace hc {

HC_API void *allocate(std::size_t size);
HC_API void *allocate_aligned(std::size_t size, std::size_t alignment);
HC_API void *reallocate(void *ptr, std::size_t size);
HC_API void *reallocate_aligned(void *ptr, std::size_t size, std::size_t alignment); // DO NOT CHANGE ALIGNMENT OF INITIAL ALLOCATION
HC_API void  free(void *ptr) noexcept;
HC_API void  free_aligned(void *ptr) noexcept;

}

#endif // HC_MEMORY_HPP
