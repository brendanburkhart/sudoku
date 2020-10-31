#include "../../src/solver/options.hpp"

#include <array>

#include "gtest/gtest.h"

TEST(OptionsTest, contains_single) {
    for (int n = 1; n <= 9; n++) {
        const solver::Options options(n);

        for (int m = 1; m <= 9; m++) {
            EXPECT_EQ(n == m, options.contains(m));
        }
    }
}

TEST(OptionsTest, solved_single) {
    const solver::Options all;
    EXPECT_EQ(false, all.solved());

    for (int n = 1; n <= 9; n++) {
        const solver::Options single(n);

        EXPECT_EQ(true, single.solved());
    }
}

TEST(OptionsTest, value_accessor) {
    const solver::Options all;
    EXPECT_EQ(0, all.value());

    for (int n = 1; n <= 9; n++) {
        const solver::Options options(n);

        EXPECT_EQ(n, options.value());
    }
}

TEST(OptionsTest, remove_ordered) {
    solver::Options options;

    for (int n = 1; n <= 8; n++) {
        EXPECT_EQ(false, options.solved());
        EXPECT_EQ(0, options.value());
        EXPECT_EQ(true, options.contains(n));

        options -= n;

        EXPECT_EQ(false, options.contains(n));
    }

    EXPECT_EQ(true, options.solved());
    EXPECT_EQ(9, options.value());
}

TEST(OptionsTest, remove_disordered) {
    std::array<int, 8> values { 3, 1, 7, 4, 5, 9, 8, 2 };

    solver::Options options;

    for (int n : values) {
        EXPECT_EQ(false, options.solved());
        EXPECT_EQ(0, options.value());
        EXPECT_EQ(true, options.contains(n));

        options -= n;

        EXPECT_EQ(false, options.contains(n));
    }

    EXPECT_EQ(true, options.solved());
    EXPECT_EQ(6, options.value());
}

TEST(OptionsTest, combine) {
    solver::Options options;
    options -= 7;
    options -= 3;
    options -= 5;
    options -= 2;

    solver::Options other;
    options -= 1;
    options -= 2;
    options -= 4;
    options -= 6;
    options -= 9;

    options &= other;

    EXPECT_EQ(false, options.contains(1));
    EXPECT_EQ(false, options.contains(2));
    EXPECT_EQ(false, options.contains(3));
    EXPECT_EQ(false, options.contains(4));
    EXPECT_EQ(false, options.contains(5));
    EXPECT_EQ(false, options.contains(6));
    EXPECT_EQ(false, options.contains(7));
    EXPECT_EQ(false, options.contains(9));

    EXPECT_EQ(true, options.solved());
    EXPECT_EQ(8, options.value());
}
