cmake_minimum_required(VERSION 3.19)
project(halocore VERSION 0.0.1 LANGUAGES CXX)

include(GNUInstallDirs)

add_library(halocore
    include/halocore/hc_def.hpp
    include/halocore/hc_type_traits.hpp
    include/halocore/hc_concepts.hpp
    include/halocore/hc_compare.hpp
    include/halocore/hc_memory_resource.hpp
    include/halocore/hc_overloaded.hpp
    include/halocore/hc_hash.hpp
    include/halocore/hc_bitflags.hpp
    include/halocore/hc_memory.hpp
    include/halocore/hc_allocator.hpp
)

target_include_directories(halocore PUBLIC include)
target_compile_features(halocore PUBLIC cxx_std_20)
if(BUILD_SHARED_LIBS)
    target_compile_definitions(halocore PUBLIC HC_DLL)
    target_compile_definitions(halocore PRIVATE HC_EXPORTING)
endif()

add_subdirectory(src)

install(TARGETS halocore
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
