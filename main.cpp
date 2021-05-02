#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"


/* DELETE THIS FILE IN FUTURE AND USE ONLY FOR CUSTOM TESTS */

int main() {
    half_float::halfsr a(-1.0 / 3.0);
    std::cout << a << std::endl;
    std::cout << 1.0f / 3.0f << std::endl;
    std::cout << std::numeric_limits<float>::max();
}