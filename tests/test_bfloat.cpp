#include <iostream>

#include "gtest/gtest.h"
#include "types.hpp"


TEST(bfloat_test_case, size_test) {
    rndcmp::bfloat16 val(0.f);
    EXPECT_EQ(sizeof(val), 2) << "expected sizeof half be 2 bytes, not " << sizeof(val);
}

TEST(bfloatsr_test_case, size_test) {
    rndcmp::bfloat16 val(0.f);
    EXPECT_EQ(sizeof(val), 2) << "expected sizeof half be 2 bytes, not " << sizeof(val);
}
