#include <cstdint>
#include <iostream>
#include "types.hpp"


int main() {
    std::cout.precision(10);
    std::cout.setf(std::ios::fixed);
    rndcmp::FloatSR aa(10);
    std::cout << aa << std::endl;
    // Works fine!
    rndcmp::Fixed a = rndcmp::Fixed<std::int16_t, 8>(3.14);
    // Also works fine!
    double value = 0.42;
    rndcmp::Fixed b = rndcmp::Fixed<std::int32_t, 16>(value);
    // Check int types
    std::int32_t int_value = 42;
    rndcmp::Fixed c = rndcmp::Fixed<std::int32_t, 16>(int_value);
    // But if we try a different type we will get an error at compile stage:
    // std::int64_t err_int_value = 42;
    // rndcmp::Fixed d = rndcmp::Fixed<std::int32_t, 16>(err_int_value);

    // Also fails on compilation stage:
    // rndcmp::Fixed a = rndcmp::Fixed<std::int16_t, 8>("stringtype");
    // or
    // rndcmp::Fixed a = rndcmp::Fixed<std::int16_t, 8>(10);
    std::cout << sizeof(rndcmp::Fixed<std::int32_t, 16>) << std::endl;

    rndcmp::FixedSR c_sr = rndcmp::FixedSR<std::int32_t, 16>(2.1);
    std::cout << 10.0 * c_sr + 3.2 << std::endl;
    return 0;
}