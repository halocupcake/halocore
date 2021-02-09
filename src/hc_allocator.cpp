#include <halocore/hc_allocator.hpp>
#include <halocore/hc_memory.hpp>

#include <cassert>

#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace hc {

void *memory_context::do_allocate(std::size_t bytes, std::size_t alignment)
{
    return allocate_aligned(bytes, alignment);
}

void *memory_context::do_reallocate(void *const ptr, std::size_t bytes, std::size_t alignment)
{
    return reallocate_aligned(ptr, bytes, alignment);
}

void *memory_context::reallocate(void *const ptr, std::size_t bytes, std::size_t alignment)
{
    return do_reallocate(ptr, bytes, alignment);
}

void memory_context::do_deallocate(void *const ptr, std::size_t bytes, std::size_t alignment)
{
    free_aligned(ptr);
}

bool memory_context::do_is_equal(std::pmr::memory_resource const &mr) const noexcept
{
    return this == &mr;
}

debug_memory_context::debug_memory_context(std::string_view identifier, source_location const sl)
    : identifier_{ identifier }
    , source_location_{ sl }
    , memory_infos_{}
    , is_missing_memory_info_{ false }
    , total_allocation_count_{ 0 }
    , bytes_allocated_{ 0 }
    , bytes_deallocated_{ 0 }
{}

debug_memory_context::debug_memory_context(debug_memory_context const &dmc)
    : identifier_{ dmc.identifier_ }
    , source_location_{ dmc.source_location_ }
    , memory_infos_{ dmc.memory_infos_ }
    , is_missing_memory_info_{ dmc.is_missing_memory_info_ }
    , total_allocation_count_{ dmc.total_allocation_count_ }
    , bytes_allocated_{ dmc.bytes_allocated_ }
    , bytes_deallocated_{ dmc.bytes_deallocated_ }
{}

debug_memory_context::~debug_memory_context()
{
    using std::setw;
    using std::left;
    using std::right;
    using std::boolalpha;

    constexpr unsigned iolw = 24, iorw = 20;

    std::cout << "debug_memory_context [" << identifier_ << "] destruction info:\n"
              << "\tcreated in " << source_location_.get_file() << " at line " << source_location_.get_line() << '\n'
              << "\t" << setw(iolw) << left << "is missing memory info: " << setw(iorw) << right << boolalpha << is_missing_memory_info_ << '\n'
              << "\t" << setw(iolw) << left << "total allocation count: " << setw(iorw) << right << total_allocation_count_ << '\n'
              << "\t" << setw(iolw) << left << "remaining allocations: "  << setw(iorw) << right << memory_infos_.size()    << '\n'
              << "\t" << setw(iolw) << left << "bytes allocated: "        << setw(iorw) << right << bytes_allocated_        << '\n'
              << "\t" << setw(iolw) << left << "bytes deallocated: "      << setw(iorw) << right << bytes_deallocated_      << '\n';
    if (!memory_infos_.empty()) {
        std::cout << "\tmemory info for remaining allocations:\n";
        for (auto const &pair : memory_infos_) {
            auto const &memory_info = pair.second;
            std::cout << "\t\taddress " << memory_info.address << ":\n"
                      << "\t\t\t" << setw(iolw) << left << "size: "               << setw(iorw) << right << memory_info.size               << '\n'
                      << "\t\t\t" << setw(iolw) << left << "alignment: "          << setw(iorw) << right << memory_info.alignment          << '\n'
                      << "\t\t\t" << setw(iolw) << left << "reallocation_count: " << setw(iorw) << right << memory_info.reallocation_count << '\n';
        }
    }

    // note to god: please grant me std::format support
}

void *debug_memory_context::do_allocate(std::size_t bytes, std::size_t alignment)
{
    void *const ptr = allocate_aligned(bytes, alignment);
    try {
        memory_infos_.emplace(ptr, memory_info{
                                  .address            = ptr,
                                  .size               = bytes,
                                  .alignment          = alignment,
                                  .reallocation_count = 0
                              });
    } catch (std::exception &e) {
        std::cerr << "error emplacing a memory_info object during an allocation!\n";
        is_missing_memory_info_ = true;
    }

    total_allocation_count_++;
    bytes_allocated_ += bytes;

    return ptr;
}

void *debug_memory_context::do_reallocate(void *const ptr, std::size_t bytes, std::size_t alignment)
{
    void *const new_ptr = reallocate_aligned(ptr, bytes, alignment);

    auto memory_info_it = memory_infos_.find(ptr);
    if (memory_info_it != memory_infos_.end()) {
        auto old_memory_info = memory_info_it->second;

        if (old_memory_info.alignment != alignment)
            std::cerr << "trying to reallocate with a different alignment!\n";

        bytes_deallocated_ += old_memory_info.size;

        if (ptr == new_ptr) {
            old_memory_info.size = bytes;
            old_memory_info.reallocation_count++;
        } else {
            memory_infos_.erase(memory_info_it);
            try {
                memory_infos_.emplace(new_ptr, memory_info{
                                          .address            = new_ptr,
                                          .size               = bytes,
                                          .alignment          = alignment,
                                          .reallocation_count = old_memory_info.reallocation_count + 1
                                      });
            } catch (std::exception &e) {
                std::cerr << "error emplacing a memory_info object during a reallocation!\n" << e.what();
                is_missing_memory_info_ = true;
            }
        }
    } else {
        std::cerr << "couldn't find memory_info object for a reallocation!\n";
    }

    total_allocation_count_++;
    bytes_allocated_ += bytes;

    return new_ptr;
}

void debug_memory_context::do_deallocate(void *const ptr, std::size_t bytes, std::size_t alignment)
{
    if (ptr) {
        free_aligned(ptr);
        bytes_deallocated_ += bytes;
        auto memory_info_it = memory_infos_.find(ptr);
        if (memory_info_it != memory_infos_.end())
            memory_infos_.erase(memory_info_it);
        else
            std::cerr << "couldn't find memory_info object for a deallocation!\n\taddress: " << ptr << "\n\tsize " << bytes << '\n';
    }
}

bool debug_memory_context::do_is_equal(std::pmr::memory_resource const &mr) const noexcept
{
    return this == &mr;
}

}
