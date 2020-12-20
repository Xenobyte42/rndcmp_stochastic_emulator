cmake_minimum_required(VERSION 3.13)

project(rndcmp_stochastic_emulator)
set(CMAKE_CXX_STANDARD 17)

#### SRC ####
ADD_SUBDIRECTORY (src)

#### HEADERS ####
include_directories (include)

set (
    HEADERS

    include/fixed_point.hpp
)

set (
    SRCS

    src/fixed_point.cpp
)

set (CONTENT ${HEADERS} ${SRCS})

add_executable(example src/example.cpp ${CONTENT})
add_executable(main main.cpp ${CONTENT})
