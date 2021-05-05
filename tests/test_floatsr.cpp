#include <iostream>

#include "gtest/gtest.h"
#include "types.hpp"


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

TEST(floatsr_test_case, size_test) {
    rndcmp::FloatSR val = 1.0;
    EXPECT_EQ(sizeof(val), 4) << "expected sizeof floatsr be 4 bytes, not " << sizeof(val);
}

TEST(floatsr_test_case, operators_test) {
    rndcmp::FloatSR val = 0.5;
    EXPECT_EQ(val == 0.5, true);
    EXPECT_EQ(val <= 0.5, true);
    EXPECT_EQ(val >= 0.5, true);
    EXPECT_EQ(val > 0.1, true);
    EXPECT_EQ(val < 0.9, true);

    rndcmp::FloatSR val2 = 1.0;
    EXPECT_EQ(val2 == 1, true);
    EXPECT_EQ(val2 > 0, true);
    EXPECT_EQ(val2 < 2, true);
    EXPECT_EQ(val2 <= 1, true);
    EXPECT_EQ(val2 >= 1, true);

    EXPECT_EQ(val < val2, true);
}

TEST(floatsr_test_case, math_expectation) {
    double val = 1.0 / 3.0;
    float float_upper = static_cast<float>(val);
    float float_lower = std::nextafterf(float_upper, 0.0f);

    double double_lower = static_cast<double>(float_lower);
    double double_upper = static_cast<double>(float_upper);

    double p_up = (val - double_lower) / (double_upper - double_lower);

    size_t N = 10000000;
    int64_t round_up_cnt = 0;
    for (size_t i = 0; i < N; i++) {
        rndcmp::FloatSR sr_val = rndcmp::FloatSR(val);
        if (sr_val > val) {
            round_up_cnt++;
        }
    }

    double received_p = static_cast<double>(round_up_cnt) / static_cast<double>(N);

    EXPECT_NEAR(received_p, p_up, 0.001);
}

TEST(floatsr_test_case, overflow_test) {
    double val = 1.1e100;
    rndcmp::FloatSR sr_val = rndcmp::FloatSR(val);

    EXPECT_NEAR(static_cast<float>(sr_val), std::numeric_limits<float>::max(), 1e-5);

    val = -val;
    sr_val = val;
    EXPECT_NEAR(static_cast<float>(sr_val), std::numeric_limits<float>::lowest(), 1e-5);
}
