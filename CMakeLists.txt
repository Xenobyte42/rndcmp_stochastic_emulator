cmake_minimum_required(VERSION 3.13)

project(rndcmp_stochastic_emulator)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

#### SRC ####
ADD_SUBDIRECTORY (src)

#### HEADERS ####
include_directories (include)

set (
    HEADERS

    include/fixed_point.hpp
)

set (CONTENT ${HEADERS} )

add_executable(main src/${SOURCE_FILES})
