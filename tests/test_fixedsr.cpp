#include <iostream>

#include "gtest/gtest.h"
#include "fixed_point.hpp"


TEST(fp_test_case, integer_precision_test)
{
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::FixedPoint val = rndcmp::FixedPoint<std::int16_t, 8>(expected);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(fp_test_case, integer_constructor_test)
{
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::FixedPoint val = rndcmp::FixedPoint<std::int16_t, 8>(1);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}
