#include <fixed_point.hpp>
#include <cstdint>
#include <iostream>


int main() {
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
    return 0;
}