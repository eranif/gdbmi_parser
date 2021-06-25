cmake_minimum_required(VERSION 3.20)

project(gdbmi_parser)

# Abseil requires C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MINGW)
    add_definitions(-D__clang_major__=0)
endif()

# Process Abseil's CMake build system
add_subdirectory(abseil-cpp)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(gdbmi_parser src/gdbmi.cpp
                         src/gdbmi.hpp)

add_executable(gdbmi_test src/main.cpp)

# Declare dependency on the absl::strings library
target_link_libraries(gdbmi_parser 
                        absl::strings 
                        absl::base 
                        absl::hash 
                        absl::flat_hash_map 
                        absl::flat_hash_set)

target_link_libraries(gdbmi_test gdbmi_parser)

