// Copyright 2021 Diakonov Andrey

#include <gtest/gtest.h>
#include <fstream>

extern "C" {
#include "service_module/include/lib_stress_test.h"
}


TEST(MATRIX_STRESS_TEST, ALL_FUNCTIONS) {
    EXPECT_EQ(read_and_compare(), 0);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
