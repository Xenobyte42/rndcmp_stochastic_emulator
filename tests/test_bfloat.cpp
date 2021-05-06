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
