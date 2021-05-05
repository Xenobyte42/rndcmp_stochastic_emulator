#include <iostream>

#include "gtest/gtest.h"
#include "types.hpp"


TEST(half_test_case, size_test) {
    half_float::half val(0.f);
    EXPECT_EQ(sizeof(val), 2) << "expected sizeof half be 2 bytes, not " << sizeof(val);
}

TEST(halfsr_test_case, size_test) {
    half_float::halfsr val(0.f);
    EXPECT_EQ(sizeof(val), 2) << "expected sizeof half be 2 bytes, not " << sizeof(val);
}
