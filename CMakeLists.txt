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

### BOOST ###

set(THIRD_PARTY ${CMAKE_SOURCE_DIR}/thirdparty)
file(MAKE_DIRECTORY ${THIRD_PARTY})


set(BOOST_ENABLE_CMAKE ON)
set(ENV{CXX} "${CMAKE_CXX_COMPILER}")

if(NOT EXISTS "${THIRD_PARTY}/boost/")
    message(NOTICE "Fetching Boost...")
    FetchContent_Declare(
        boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG        boost-1.75.0
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
        SOURCE_DIR     ${THIRD_PARTY}/boost
    )
    FetchContent_GetProperties(boost)
    if(NOT boost_POPULATED)
        FetchContent_Populate(boost)
    endif()
    if(UNIX)
        execute_process (
            COMMAND ./bootstrap.sh
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${boost_SOURCE_DIR}
        )
        if(NOT result EQUAL 0)
            message( FATAL_ERROR "Failed to build Boost: ${result}")
        endif()
        execute_process (
            COMMAND ./b2 headers
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${boost_SOURCE_DIR}
        )
        if(NOT result EQUAL 0)
            message( FATAL_ERROR "Failed to build Boost: ${result}")
        endif()
    elseif(WIN32)
        execute_process (
            COMMAND ./bootstrap.bat
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${boost_SOURCE_DIR}
        )
        execute_process (
            COMMAND b2 headers
            RESULT_VARIABLE result
            WORKING_DIRECTORY ${boost_SOURCE_DIR}
        )
    endif()
endif()

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

set(BOOST_ROOT ${THIRD_PARTY}/boost)
find_package(Boost 1.73.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost is not found.")
endif()

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
add_executable(main main.cpp ${CONTENT})
add_executable(integrator_example examples/integrator_example.cpp ${CONTENT})
add_executable(experiment1 experiments/experiment1.cpp ${CONTENT})
add_executable(experiment2 experiments/experiment2.cpp ${CONTENT})
add_executable(experiment3 experiments/experiment3.cpp ${CONTENT})
add_executable(experiment4 experiments/experiment4.cpp ${CONTENT})

target_link_libraries(main PRIVATE Boost::boost)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test_main ${CONTENT_TEST})
target_link_libraries(test_main gtest_main)

enable_testing()
add_test(NAME test_main COMMAND test)