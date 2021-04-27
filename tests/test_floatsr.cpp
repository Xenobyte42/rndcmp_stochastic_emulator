#include <iostream>

#include "gtest/gtest.h"
#include "floatsr.hpp"


TEST(floatsr_test_case, integer_precision_test) {
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::FloatSR val = rndcmp::FloatSR(expected);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(floatsr_test_case, integer_constructor_test) {
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::FloatSR val = rndcmp::FloatSR(1);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(floatsr_test_case, base_two_test) {
    // 2^(-p) should never round up or down
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 0.5;
        rndcmp::FloatSR val = rndcmp::FloatSR(expected);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(floatsr_test_case, stochastic_rounding_test) {
    size_t N = 10000;
    int64_t rounds_up_cnt = 0;
    int64_t rounds_down_cnt = 0;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0 / 3.0;
        rndcmp::FloatSR val = rndcmp::FloatSR(expected);
        if (expected > val) {
            rounds_down_cnt++;
        } else {
            rounds_up_cnt++;
        }
    }
    EXPECT_GT(rounds_up_cnt, 0) << "the number of rounds up is expected to be greater than 0";
    EXPECT_GT(rounds_down_cnt, 0) << "the number of rounds down is expected to be greater than 0";
}
