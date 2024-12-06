cmake_minimum_required(VERSION 3.21)

# This project is organized based on Boris Kolpackov's Canonical Project Structure:
# https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html

project(acquisition
    VERSION 2.0
    DESCRIPTION "Stash and forum shop management for Path of Exile \\256"
    HOMEPAGE_URL "https://github.com/gerwaric/acquisition"
    LANGUAGES CXX
)

# Compiler options need to be set before calling the qt setup functions. This was
# a bother to figure out.
if(MSVC)
    add_compile_options(/EHsc)
    add_compile_options(/W4)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    HttpServer
    Network
    Quick
    Sql
)

qt_standard_project_setup(REQUIRES 6.8)

# The main executable
add_subdirectory(acquisition)

# The main library
add_subdirectory(libacq)

# External libraries used by acquisition
add_subdirectory(external/boost-headers-only)
add_subdirectory(external/json_struct)
add_subdirectory(external/QsLog)
