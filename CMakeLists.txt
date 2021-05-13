cmake_minimum_required(VERSION 3.13)
project(rndcmp_stochastic_emulator)
set(CMAKE_CXX_STANDARD 17)

### GOOGLE TEST ###

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


### EIGEN ###

find_package (Eigen3 3.3 REQUIRED NO_MODULE)


#### SRC ####
ADD_SUBDIRECTORY (src)

#### HEADERS ####
include_directories (include)

#### TESTS ####
ADD_SUBDIRECTORY(tests)

set (
    HEADERS

    include/fixedsr.hpp
    include/fixed.hpp
    include/floatsr.hpp
    include/types.hpp
    include/half.hpp
    include/halfsr.hpp
    include/bfloat16.hpp
    include/bfloat16sr.hpp

    include/integrator.hpp
    include/esn.hpp
)

set (
    SRCS

    
)

set (
    TESTS

    tests/test_fixedsr.cpp
    tests/test_floatsr.cpp
    tests/test_bfloat.cpp
    tests/test_half.cpp
)

set (CONTENT ${HEADERS} ${SRCS})
set (CONTENT_TEST ${HEADERS} ${SRCS} ${TESTS})

add_executable(example examples/example.cpp ${CONTENT})
target_link_libraries(example Eigen3::Eigen)

add_executable(main main.cpp ${CONTENT})
target_link_libraries(main Eigen3::Eigen)

add_executable(integrator_example examples/integrator_example.cpp ${CONTENT})
target_link_libraries(integrator_example Eigen3::Eigen)

add_executable(experiment1 experiments/experiment1.cpp ${CONTENT})
target_link_libraries(experiment1 Eigen3::Eigen)

add_executable(experiment2 experiments/experiment2.cpp ${CONTENT})
target_link_libraries(experiment2 Eigen3::Eigen)

add_executable(experiment3 experiments/experiment3.cpp ${CONTENT})
target_link_libraries(experiment3 Eigen3::Eigen)

add_executable(experiment4 experiments/experiment4.cpp ${CONTENT})
target_link_libraries(experiment4 Eigen3::Eigen)

add_executable(experiment5 experiments/experiment5.cpp ${CONTENT})
target_link_libraries(experiment5 Eigen3::Eigen)



# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_main ${CONTENT_TEST})
target_link_libraries(test_main gtest_main Eigen3::Eigen)

enable_testing()
add_test(NAME test_main COMMAND test)