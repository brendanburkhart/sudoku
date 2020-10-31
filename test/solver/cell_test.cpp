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

TEST(CellTest, eliminate) {
    solver::Cell cell;

    solver::Options options;
    options -= 5;

    cell.eliminate(options);
    EXPECT_EQ(false, cell.could_be(5));

    options -= 1;
    options -= 2;
    options -= 7;

    cell.eliminate(options);

    EXPECT_EQ(false, cell.could_be(1));
    EXPECT_EQ(false, cell.could_be(2));
    EXPECT_EQ(false, cell.could_be(5));
    EXPECT_EQ(false, cell.could_be(7));
    EXPECT_EQ(true, cell.could_be(3));
    EXPECT_EQ(true, cell.could_be(4));
    EXPECT_EQ(true, cell.could_be(6));
    EXPECT_EQ(true, cell.could_be(8));
    EXPECT_EQ(true, cell.could_be(9));
}

TEST(CellTest, eliminate_single) {
    solver::Cell cell(5);

    EXPECT_EQ(true, cell.could_be(5));

    solver::Options options;
    options -= 5;

    cell.eliminate(options);
    EXPECT_EQ(true, cell.could_be(5));
}

TEST(CellTest, eliminate_is_idempotent) {
    solver::Cell cell;

    solver::Options options;
    options -= 5;

    cell.eliminate(options);
    EXPECT_EQ(false, cell.could_be(5));

    options -= 1;
    options -= 2;
    options -= 7;

    cell.eliminate(options);

    EXPECT_EQ(false, cell.could_be(1));
    EXPECT_EQ(false, cell.could_be(2));
    EXPECT_EQ(false, cell.could_be(5));
    EXPECT_EQ(false, cell.could_be(7));
    EXPECT_EQ(true, cell.could_be(3));
    EXPECT_EQ(true, cell.could_be(4));
    EXPECT_EQ(true, cell.could_be(6));
    EXPECT_EQ(true, cell.could_be(8));
    EXPECT_EQ(true, cell.could_be(9));

    cell.eliminate(options);

    EXPECT_EQ(false, cell.could_be(1));
    EXPECT_EQ(false, cell.could_be(2));
    EXPECT_EQ(false, cell.could_be(5));
    EXPECT_EQ(false, cell.could_be(7));
    EXPECT_EQ(true, cell.could_be(3));
    EXPECT_EQ(true, cell.could_be(4));
    EXPECT_EQ(true, cell.could_be(6));
    EXPECT_EQ(true, cell.could_be(8));
    EXPECT_EQ(true, cell.could_be(9));
}

TEST(CellTest, eliminate_update) {
    solver::Cell cell;

    solver::Options options;
    options -= 1;
    options -= 2;
    options -= 3;
    options -= 4;
    options -= 6;
    options -= 7;
    options -= 8;
    options -= 9;

    cell.eliminate(options);
    cell.update();

    EXPECT_EQ(5, cell.get_value());
}

TEST(CellTest, update_is_idempotent) {
    solver::Cell cell;

    solver::Options options;
    options -= 1;
    options -= 2;
    options -= 3;
    options -= 4;

    cell.eliminate(options);
    cell.update();
    EXPECT_EQ(0, cell.get_value());

    options -= 6;
    options -= 7;
    options -= 8;
    options -= 9;

    cell.eliminate(options);
    cell.update();

    EXPECT_EQ(5, cell.get_value());

    cell.update();

    EXPECT_EQ(5, cell.get_value());
}
