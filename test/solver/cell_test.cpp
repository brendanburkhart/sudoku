#include "../../src/solver/cell.hpp"

#include "gtest/gtest.h"

TEST(CellTest, initial_value) {
    const solver::Cell cell;
    EXPECT_EQ(0, cell.get_value());

    for (int n = 1; n <= 9; n++) {
        const solver::Cell cell(n);
        EXPECT_EQ(n, cell.get_value());
    }
}

TEST(CellTest, could_be) {
    const solver::Cell cell;

    for (int n = 1; n <= 9; n++) {
        EXPECT_EQ(true, cell.could_be(n));
    }

    for (int n = 1; n <= 9; n++) {
        const solver::Cell cell(n);

        for (int m = 1; m <= 9; m++) {
            EXPECT_EQ(n == m, cell.could_be(m));
        }
    }
}
