target_sources(halocore
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/hc_memory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/hc_allocator.cpp
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_sources(halocore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/hc_memory_msvc.cpp)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        target_sources(halocore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/hc_memory_msvc.cpp)
    else()
        target_sources(halocore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/hc_memory_std.cpp)
    endif()
else()
    target_sources(halocore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/hc_memory_std.cpp)
endif()
