cmake_minimum_required(VERSION 3.16)
project(pnflow)

option(PNFLOW_WINDOWS "Cross compile for windows" OFF)

if (PNFLOW_WINDOWS)
    SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    SET(CMAKE_CXX_FLAGS "-std=c++17")
    SET(OPT ".exe")
endif()

add_subdirectory(pkgs)
add_subdirectory(src)
