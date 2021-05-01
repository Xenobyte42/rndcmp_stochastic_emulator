#include <cstdint>
#include <iostream>
#include "types.hpp"


int main() {
    std::cout.precision(10);
    std::cout.setf(std::ios::fixed);
    rndcmp::FloatSR aa(10);
    std::cout << aa << std::endl;
    // Works fine!
    rndcmp::FixedPoint a = rndcmp::FixedPoint<std::int16_t, 8>(3.14);
    // Also works fine!
    double value = 0.42;
    rndcmp::FixedPoint b = rndcmp::FixedPoint<std::int32_t, 16>(value);
    // Check int types
    std::int32_t int_value = 42;
    rndcmp::FixedPoint c = rndcmp::FixedPoint<std::int32_t, 16>(int_value);
    // But if we try a different type we will get an error at compile stage:
    // std::int64_t err_int_value = 42;
    // rndcmp::FixedPoint d = rndcmp::FixedPoint<std::int32_t, 16>(err_int_value);

    // Also fails on compilation stage:
    // rndcmp::FixedPoint a = rndcmp::FixedPoint<std::int16_t, 8>("stringtype");
    // or
    // rndcmp::FixedPoint a = rndcmp::FixedPoint<std::int16_t, 8>(10);
    std::cout << sizeof(rndcmp::FixedPoint<std::int32_t, 16>) << std::endl;

    rndcmp::FixedPointSR c_sr = rndcmp::FixedPointSR<std::int32_t, 16>(2.1);
    std::cout << 10.0 * c_sr + 3.2 << std::endl;
    return 0;
}