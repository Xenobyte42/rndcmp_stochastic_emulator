#include <fixed_point.hpp>
#include <cstdint>

int main() {
    // Works fine!
    rndcmp::FixedPoint a = rndcmp::FixedPoint<std::int16_t, 8>(3.14);
    // Also works fine!
    double value = 0.42;
    rndcmp::FixedPoint b = rndcmp::FixedPoint<std::int32_t, 16>(value);
    // Fails on compilation stage:
    // rndcmp::FixedPoint a = rndcmp::FixedPoint<std::int16_t, 8>("stringtype");
    // or
    // rndcmp::FixedPoint a = rndcmp::FixedPoint<std::int16_t, 8>(10);

    return 0;
}