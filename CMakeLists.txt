cmake_minimum_required(VERSION 3.20)

project(gdbmi_parser)

# Abseil requires C++11
set(CMAKE_CXX_STANDARD 11)

if (MINGW)
    add_definitions(-D__clang_major__=0)
endif()

# Process Abseil's CMake build system
add_subdirectory(abseil-cpp)

add_library(gdbmi_parser src/gdbmi.cpp
                         src/gdbmi.hpp)

if (MINGW)
    set(INCLUDE_PATHS $ENV{CXX_INCLUDE_PATHS})
    foreach(INCLUDE_PATH ${INCLUDE_PATHS})
        add_definitions(-I"${INCLUDE_PATH}")
    endforeach()
endif()

# Declare dependency on the absl::strings library
target_link_libraries(gdbmi_parser absl::strings)

execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json 
                ${CMAKE_SOURCE_DIR}/compile_commands.json)
