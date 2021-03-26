#ifndef HC_MEMORY_RESOURCE_HPP
#define HC_MEMORY_RESOURCE_HPP

#if __has_include(<memory_resource>)
#    include <memory_resource>
#elif __has_include(<experimental/memory_resource>)
#    include <experimental/memory_resource>
#else
#    error "can't find memory_resource header!"
#endif

#endif // HC_MEMORY_RESOURCE_HPP
