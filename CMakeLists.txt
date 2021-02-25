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
    include/integrator.hpp

    include/floatsr.hpp
)

set (
    SRCS

    src/fixed_point.cpp
)

set (CONTENT ${HEADERS} ${SRCS})

add_executable(example example.cpp ${CONTENT})
add_executable(main main.cpp ${CONTENT})
add_executable(integrator_example integrator_example.cpp ${CONTENT})
add_executable(experiment1 experiment1.cpp ${CONTENT})
add_executable(experiment2 experiment2.cpp ${CONTENT})
add_executable(experiment3 experiment3.cpp ${CONTENT})
add_executable(experiment4 experiment4.cpp ${CONTENT})
