#include <iostream>
#include <cstdint>
#include "types.hpp"
#include "integrator.hpp"


/* DELETE THIS FILE IN FUTURE AND USE ONLY FOR CUSTOM TESTS */

int main() {
    rndcmp::bfloat16sr a(-1.0f / 3.0f);
    a = a - 4.0;
    std::cout << a << std::endl;
}