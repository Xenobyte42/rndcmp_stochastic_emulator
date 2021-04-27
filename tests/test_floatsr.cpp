#include <iostream>

#include "gtest/gtest.h"
#include "floatsr.hpp"


TEST(floatsr_test_case, integer_precision_test)
{
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::FloatSR val = rndcmp::FloatSR(expected);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(floatsr_test_case, integer_constructor_test)
{
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::FloatSR val = rndcmp::FloatSR(1);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}