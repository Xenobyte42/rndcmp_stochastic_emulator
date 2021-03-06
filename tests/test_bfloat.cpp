#include <iostream>

#include "gtest/gtest.h"
#include "bfloat16.hpp"
#include "bfloat16sr.hpp"


/* Bfloat test cases */

TEST(bfloat_test_case, size_test) {
    rndcmp::bfloat16 val(0.f);
    EXPECT_EQ(sizeof(val), 2) << "expected sizeof half be 2 bytes, not " << sizeof(val);
}

TEST(bfloat_test_case, integer_precision_test) {
    double expected = 1.0;
    rndcmp::bfloat16 val = expected;
    EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    EXPECT_EQ(-expected, static_cast<double>(-val)) << "expected: " << expected << "received: " << val;
}

TEST(bfloat_test_case, operators_test) {
    rndcmp::bfloat16 val = 0.5;
    EXPECT_EQ(val == 0.5, true);
    EXPECT_EQ(val <= 0.5, true);
    EXPECT_EQ(val >= 0.5, true);
    EXPECT_EQ(val > 0.1, true);
    EXPECT_EQ(val < 0.9, true);

    rndcmp::bfloat16 val2 = 1.0;
    EXPECT_EQ(val2 == 1, true);
    EXPECT_EQ(val2 > 0, true);
    EXPECT_EQ(val2 < 2, true);
    EXPECT_EQ(val2 <= 1, true);
    EXPECT_EQ(val2 >= 1, true);

    EXPECT_EQ(val < val2, true);
}

TEST(bfloat_test_case, math_functions_test) {
    EXPECT_EQ(cos(rndcmp::bfloat16(0.0)), 1);
    EXPECT_EQ(sin(rndcmp::bfloat16(0.0)), 0);

    EXPECT_EQ(cosh(rndcmp::bfloat16(0.0)), 1);
    EXPECT_EQ(sinh(rndcmp::bfloat16(0.0)), 0);

    EXPECT_EQ(exp(rndcmp::bfloat16(0.0)), 1);
    EXPECT_EQ(log(rndcmp::bfloat16(1.0)), 0);
    EXPECT_EQ(log10(rndcmp::bfloat16(100.0)), 2);

    EXPECT_EQ(pow(rndcmp::bfloat16(2.5), 2), 6.25);
    EXPECT_EQ(sqrt(rndcmp::bfloat16(6.25)), 2.5);
    EXPECT_EQ(cbrt(rndcmp::bfloat16(8)), 2);

    EXPECT_EQ(abs(rndcmp::bfloat16(-2.5)), 2.5);
}

/* BfloatSR test cases */

TEST(bfloatsr_test_case, size_test) {
    rndcmp::bfloat16 val(0.f);
    EXPECT_EQ(sizeof(val), 2) << "expected sizeof half be 2 bytes, not " << sizeof(val);
}

TEST(bfloatsr_test_case, integer_precision_test) {
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::bfloat16sr val = expected;
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
        EXPECT_EQ(-expected, static_cast<double>(-val)) << "expected: " << -expected << "received: " << -val;
    }
}

TEST(bfloatsr_test_case, integer_constructor_test) {
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::bfloat16sr val = 1;
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(bfloatsr_test_case, base_two_test) {
    // 2^(-p) should never round up or down
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 0.5;
        rndcmp::bfloat16sr val(expected);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(bfloatsr_test_case, stochastic_rounding_test) {
    size_t N = 10000;
    int64_t rounds_up_cnt = 0;
    int64_t rounds_down_cnt = 0;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0 / 3.0;
        rndcmp::bfloat16sr val(expected);
        if (expected > val) {
            rounds_down_cnt++;
        } else {
            rounds_up_cnt++;
        }
    }
    EXPECT_GT(rounds_up_cnt, 0) << "the number of rounds up is expected to be greater than 0";
    EXPECT_GT(rounds_down_cnt, 0) << "the number of rounds down is expected to be greater than 0";
}

TEST(bfloatsr_test_case, operators_test) {
    rndcmp::bfloat16sr val = 0.5;
    EXPECT_EQ(val == 0.5, true);
    EXPECT_EQ(val <= 0.5, true);
    EXPECT_EQ(val >= 0.5, true);
    EXPECT_EQ(val > 0.1, true);
    EXPECT_EQ(val < 0.9, true);

    rndcmp::bfloat16sr val2 = 1.0;
    EXPECT_EQ(val2 == 1, true);
    EXPECT_EQ(val2 > 0, true);
    EXPECT_EQ(val2 < 2, true);
    EXPECT_EQ(val2 <= 1, true);
    EXPECT_EQ(val2 >= 1, true);

    EXPECT_EQ(val < val2, true);
}

TEST(bfloatsr_test_case, math_functions_test) {
    EXPECT_EQ(cos(rndcmp::bfloat16sr(0.0)), 1);
    EXPECT_EQ(sin(rndcmp::bfloat16sr(0.0)), 0);

    EXPECT_EQ(cosh(rndcmp::bfloat16sr(0.0)), 1);
    EXPECT_EQ(sinh(rndcmp::bfloat16sr(0.0)), 0);

    EXPECT_EQ(exp(rndcmp::bfloat16sr(0.0)), 1);
    EXPECT_EQ(log(rndcmp::bfloat16sr(1.0)), 0);
    EXPECT_EQ(log10(rndcmp::bfloat16sr(100.0)), 2);

    EXPECT_EQ(pow(rndcmp::bfloat16sr(2.5), 2), 6.25);
    EXPECT_EQ(sqrt(rndcmp::bfloat16sr(6.25)), 2.5);
    EXPECT_EQ(cbrt(rndcmp::bfloat16sr(8)), 2);

    EXPECT_EQ(abs(rndcmp::bfloat16sr(-2.5)), 2.5);
}
