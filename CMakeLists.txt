# CMake build file for Gnu Dap

cmake_minimum_required (VERSION 2.8.11)
project(Dap)

add_subdirectory (src)
add_subdirectory (src/include)

add_executable (dap)
add_executable (dappp)

