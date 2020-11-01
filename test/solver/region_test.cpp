#include "../../src/solver/region.hpp"

#include "gtest/gtest.h"

TEST(RegionTest, elimination) {
    std::array<solver::Cell, 9> data;

    data[0] = solver::Cell(1);
    data[1] = solver::Cell(2);
    data[2] = solver::Cell(3);
    data[3] = solver::Cell();
    data[4] = solver::Cell();
    data[5] = solver::Cell(6);
    data[6] = solver::Cell(7);
    data[7] = solver::Cell();
    data[8] = solver::Cell(9);

    solver::Region region(std::array<solver::Cell*, 9>{
        &data[0],
        &data[1],
        &data[2],
        &data[3],
        &data[4],
        &data[5],
        &data[6],
        &data[7],
        &data[8],
    });

    region.eliminate();

    for (int n = 1; n <= 9; n++) {
        bool solved = (n != 4) && (n != 5) && (n != 8);

        for (size_t i = 0; i < 9; i++) {
            bool unsolved = (i == 3) || (i == 4) || (i == 7);
            bool could_be = (solved && (n == i + 1)) || (!solved && unsolved);

            EXPECT_EQ(could_be, data[i].could_be(n));
        }
    }
}

TEST(RegionTest, single_exclude) {
    std::array<solver::Cell, 9> data;

    data[0] = solver::Cell(1);
    data[1] = solver::Cell(2);
    data[2] = solver::Cell(3);
    data[3] = solver::Cell();
    data[4] = solver::Cell();
    data[5] = solver::Cell(6);
    data[6] = solver::Cell(7);
    data[7] = solver::Cell();
    data[8] = solver::Cell(9);

    solver::Options available;
    available -= 4;

    data[4].eliminate(available);
    data[7].eliminate(available);

    solver::Region region(std::array<solver::Cell*, 9>{
        &data[0],
        &data[1],
        &data[2],
        &data[3],
        &data[4],
        &data[5],
        &data[6],
        &data[7],
        &data[8],
    });

    EXPECT_EQ(true, data[3].could_be(4));
    EXPECT_EQ(true, data[3].could_be(6));
    EXPECT_EQ(true, data[3].could_be(8));

    region.exclude();

    EXPECT_EQ(true, data[3].could_be(4));
    EXPECT_EQ(false, data[3].could_be(6));
    EXPECT_EQ(false, data[3].could_be(8));
}
