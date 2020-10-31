#include "gtest/gtest.h"

#include "../../src/solver/options.hpp"

TEST(OptionsTest, options_contain_value)
{
    for (int n = 1; n <= 9; n++) {
        solver::Options options(n);

	    for (int m = 1; m <= 9; m++) {
            EXPECT_EQ(n == m, options.contains(m));
        }
    }
}
