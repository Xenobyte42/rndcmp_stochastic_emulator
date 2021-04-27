cmake_minimum_required(VERSION 3.13)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

project(rndcmp_stochastic_emulator)
set(CMAKE_CXX_STANDARD 17)

#### SRC ####
ADD_SUBDIRECTORY (src)

#### HEADERS ####
include_directories (include)

#### TESTS ####
ADD_SUBDIRECTORY(tests)

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

set (
    TESTS

    tests/test_fixedsr.cpp
    tests/test_floatsr.cpp
)

set (CONTENT ${HEADERS} ${SRCS})
set (CONTENT_TEST ${HEADERS} ${SRCS} ${TESTS})

add_executable(example example.cpp ${CONTENT})
add_executable(main main.cpp ${CONTENT})
add_executable(integrator_example integrator_example.cpp ${CONTENT})
add_executable(experiment1 experiment1.cpp ${CONTENT})
add_executable(experiment2 experiment2.cpp ${CONTENT})
add_executable(experiment3 experiment3.cpp ${CONTENT})
add_executable(experiment4 experiment4.cpp ${CONTENT})


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_main ${CONTENT_TEST})
target_link_libraries(test_main gtest_main)

enable_testing()
add_test(NAME test_main COMMAND test)