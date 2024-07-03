cmake_minimum_required(VERSION 3.16)
project(pnflow)

option(PNFLOW_WINDOWS "Cross compile for windows" OFF)
option(PNFLOW_AS_LIB "Build as a library instead of executable" OFF)

if (PNFLOW_WINDOWS)
    SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    SET(CMAKE_CXX_FLAGS "-std=c++17 -O3")
    SET(OPT ".exe")
else()
    SET(CMAKE_CXX_FLAGS "-O3")
endif()

add_subdirectory(pkgs)
add_subdirectory(src)
