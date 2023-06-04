# CMake build file for Gnu Dap

cmake_minimum_required (VERSION 2.8.11)
project(Dap)

add_subdirectory (src)
add_subdirectory (src/include)

add_library(libdap dap0.cpp machdep.cpp dap1.cpp dap2.cpp dap3.cpp dap4.cpp dap5.cpp dap6.cpp prob.cpp misc.cpp ps.cpp ps1.cpp
)
add_executable (dap dap.cpp)

add_executable (dappp dappp.cpp sastrans.cpp sastrans1.cpp sastrans2.cpp sastrans3.cpp)

