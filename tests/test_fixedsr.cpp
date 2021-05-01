#include <iostream>

#include "gtest/gtest.h"
#include "fixedsr.hpp"


/* Fixed point test cases */

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

TEST(fp_test_case, size_test) {
    rndcmp::FixedPoint val16 = rndcmp::FixedPoint<std::int16_t, 8>(1);
    rndcmp::FixedPoint val32 = rndcmp::FixedPoint<std::int32_t, 16>(1);

    EXPECT_EQ(sizeof(val16), 2) << "expected sizeof fp<7.8> be 2 bytes, not " << sizeof(val16);
    EXPECT_EQ(sizeof(val32), 4) << "expected sizeof fp<15.16> be 4 bytes, not " << sizeof(val32);
}

TEST(fp_test_case, operators_test) {
    rndcmp::FixedPoint val = rndcmp::FixedPoint<std::int16_t, 8>(0.5);
    EXPECT_EQ(val == 0.5, true);
    EXPECT_EQ(val <= 0.5, true);
    EXPECT_EQ(val >= 0.5, true);
    EXPECT_EQ(val > 0.1, true);
    EXPECT_EQ(val < 0.9, true);

    rndcmp::FixedPoint val2 = rndcmp::FixedPoint<std::int16_t, 8>(1);
    EXPECT_EQ(val2 == 1, true);
    EXPECT_EQ(val2 > 0, true);
    EXPECT_EQ(val2 < 2, true);
    EXPECT_EQ(val2 <= 1, true);
    EXPECT_EQ(val2 >= 1, true);

    EXPECT_EQ(val < val2, true);
}

/* Fixed point stochastic test cases */

TEST(fpsr_test_case, integer_precision_test)
{
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::FixedPointSR val = rndcmp::FixedPointSR<std::int16_t, 8>(expected);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(fpsr_test_case, integer_constructor_test)
{
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0;
        rndcmp::FixedPointSR val = rndcmp::FixedPointSR<std::int16_t, 8>(1);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(fpsr_test_case, base_two_test) {
    // 2^(-p) should never round up or down
    size_t N = 1000;
    for (size_t i = 0; i < N; i++) {
        double expected = 0.5;
        rndcmp::FixedPointSR val = rndcmp::FixedPointSR<std::int16_t, 8>(expected);
        EXPECT_EQ(expected, static_cast<double>(val)) << "expected: " << expected << "received: " << val;
    }
}

TEST(fpsr_test_case, stochastic_rounding_test) {
    size_t N = 10000;
    int64_t rounds_up_cnt = 0;
    int64_t rounds_down_cnt = 0;
    for (size_t i = 0; i < N; i++) {
        double expected = 1.0 / 3.0;
        rndcmp::FixedPointSR val = rndcmp::FixedPointSR<std::int32_t, 16>(expected);
        if (expected > val) {
            rounds_down_cnt++;
        } else {
            rounds_up_cnt++;
        }
    }
    EXPECT_GT(rounds_up_cnt, 0) << "the number of rounds up is expected to be greater than 0";
    EXPECT_GT(rounds_down_cnt, 0) << "the number of rounds down is expected to be greater than 0";
}

TEST(fpsr_test_case, size_test) {
    rndcmp::FixedPointSR val16 = rndcmp::FixedPointSR<std::int16_t, 8>(1);
    rndcmp::FixedPointSR val32 = rndcmp::FixedPointSR<std::int32_t, 16>(1);

    EXPECT_EQ(sizeof(val16), 2) << "expected sizeof fp_sr<7.8> be 2 bytes, not " << sizeof(val16);
    EXPECT_EQ(sizeof(val32), 4) << "expected sizeof fp_sr<15.16> be 4 bytes, not " << sizeof(val32);
}

TEST(fpsr_test_case, operators_test) {
    rndcmp::FixedPointSR val = rndcmp::FixedPointSR<std::int16_t, 8>(0.5);
    // This condition based on base_two_test 
    EXPECT_EQ(val == 0.5, true);
    EXPECT_EQ(val <= 0.5, true);
    EXPECT_EQ(val >= 0.5, true);
    EXPECT_EQ(val > 0.1, true);
    EXPECT_EQ(val < 0.9, true);

    rndcmp::FixedPointSR val2 = rndcmp::FixedPointSR<std::int16_t, 8>(1);
    EXPECT_EQ(val2 == 1, true);
    EXPECT_EQ(val2 > 0, true);
    EXPECT_EQ(val2 < 2, true);
    EXPECT_EQ(val2 <= 1, true);
    EXPECT_EQ(val2 >= 1, true);

    EXPECT_EQ(val < val2, true);
}
