#include "../../src/solver/region.hpp"

#include "gtest/gtest.h"

TEST(RegionTest, available_in_segment) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options(1);
    data[1] = solver::Options(2);
    data[2] = solver::Options(3);
    data[3] = solver::Options();
    data[4] = solver::Options();
    data[5] = solver::Options(6);
    data[6] = solver::Options(7);
    data[7] = solver::Options();
    data[8] = solver::Options(9);

    solver::Region region(std::array<solver::Options*, 9>{
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

    const solver::Options first_segment = region.available_in_segment(0);
    EXPECT_EQ(0, first_segment.count());

    const solver::Options second_segment = region.available_in_segment(1);
    EXPECT_EQ(3, second_segment.count());
    EXPECT_EQ(true, second_segment.overlaps(4));
    EXPECT_EQ(true, second_segment.overlaps(5));

    const solver::Options third_segment = region.available_in_segment(2);
    EXPECT_EQ(3, third_segment.count());
    EXPECT_EQ(true, third_segment.overlaps(8));
}

TEST(RegionTest, elimination) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options(1);
    data[1] = solver::Options(2);
    data[2] = solver::Options(3);
    data[3] = solver::Options();
    data[4] = solver::Options();
    data[5] = solver::Options(6);
    data[6] = solver::Options(7);
    data[7] = solver::Options();
    data[8] = solver::Options(9);

    solver::Region region(std::array<solver::Options*, 9>{
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
            bool overlaps = (solved && (n == i + 1)) || (!solved && unsolved);

            EXPECT_EQ(overlaps, data[i].overlaps(n));
        }
    }
}

TEST(RegionTest, single_exclude) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options(1);
    data[1] = solver::Options(2);
    data[2] = solver::Options(3);
    data[3] = solver::Options();
    data[4] = solver::Options();
    data[5] = solver::Options(6);
    data[6] = solver::Options(7);
    data[7] = solver::Options();
    data[8] = solver::Options(9);

    solver::Options available;
    available.remove(4);

    data[4].restrict_to(available);
    data[7].restrict_to(available);

    solver::Region region(std::array<solver::Options*, 9>{
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

    EXPECT_EQ(true, data[3].overlaps(4));
    EXPECT_EQ(true, data[3].overlaps(6));
    EXPECT_EQ(true, data[3].overlaps(8));

    region.exclude();

    EXPECT_EQ(true, data[3].overlaps(4));
    EXPECT_EQ(false, data[3].overlaps(6));
    EXPECT_EQ(false, data[3].overlaps(8));

    EXPECT_EQ(1, data[0].value());
    EXPECT_EQ(2, data[1].value());
    EXPECT_EQ(3, data[2].value());
    EXPECT_EQ(6, data[5].value());
    EXPECT_EQ(7, data[6].value());
    EXPECT_EQ(9, data[8].value());
}

TEST(RegionTest, multi_exclude) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options(1);
    data[1] = solver::Options(2);
    data[2] = solver::Options();
    data[3] = solver::Options();
    data[4] = solver::Options();
    data[5] = solver::Options(6);
    data[6] = solver::Options();
    data[7] = solver::Options();
    data[8] = solver::Options(9);

    solver::Options available;
    available.remove(3);
    available.remove(7);
    available.remove(8);

    data[3].restrict_to(available);
    data[4].restrict_to(available);

    solver::Region region(std::array<solver::Options*, 9>{
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

    EXPECT_EQ(true, data[2].overlaps(3));
    EXPECT_EQ(true, data[2].overlaps(4));
    EXPECT_EQ(true, data[2].overlaps(5));
    EXPECT_EQ(true, data[2].overlaps(7));
    EXPECT_EQ(true, data[2].overlaps(8));
    EXPECT_EQ(false, data[3].overlaps(3));
    EXPECT_EQ(true, data[3].overlaps(4));
    EXPECT_EQ(true, data[3].overlaps(5));
    EXPECT_EQ(false, data[3].overlaps(7));
    EXPECT_EQ(false, data[3].overlaps(8));
    EXPECT_EQ(false, data[4].overlaps(3));
    EXPECT_EQ(true, data[4].overlaps(4));
    EXPECT_EQ(true, data[4].overlaps(5));
    EXPECT_EQ(false, data[4].overlaps(7));
    EXPECT_EQ(false, data[4].overlaps(8));
    EXPECT_EQ(true, data[6].overlaps(3));
    EXPECT_EQ(true, data[6].overlaps(4));
    EXPECT_EQ(true, data[6].overlaps(5));
    EXPECT_EQ(true, data[6].overlaps(7));
    EXPECT_EQ(true, data[6].overlaps(8));
    EXPECT_EQ(true, data[7].overlaps(3));
    EXPECT_EQ(true, data[7].overlaps(4));
    EXPECT_EQ(true, data[7].overlaps(5));
    EXPECT_EQ(true, data[7].overlaps(7));
    EXPECT_EQ(true, data[7].overlaps(8));

    region.exclude();

    EXPECT_EQ(true, data[2].overlaps(3));
    EXPECT_EQ(false, data[2].overlaps(4));
    EXPECT_EQ(false, data[2].overlaps(5));
    EXPECT_EQ(true, data[2].overlaps(7));
    EXPECT_EQ(true, data[2].overlaps(8));
    EXPECT_EQ(false, data[3].overlaps(3));
    EXPECT_EQ(true, data[3].overlaps(4));
    EXPECT_EQ(true, data[3].overlaps(5));
    EXPECT_EQ(false, data[3].overlaps(7));
    EXPECT_EQ(false, data[3].overlaps(8));
    EXPECT_EQ(false, data[4].overlaps(3));
    EXPECT_EQ(true, data[4].overlaps(4));
    EXPECT_EQ(true, data[4].overlaps(5));
    EXPECT_EQ(false, data[4].overlaps(7));
    EXPECT_EQ(false, data[4].overlaps(8));
    EXPECT_EQ(true, data[6].overlaps(3));
    EXPECT_EQ(false, data[6].overlaps(4));
    EXPECT_EQ(false, data[6].overlaps(5));
    EXPECT_EQ(true, data[6].overlaps(7));
    EXPECT_EQ(true, data[6].overlaps(8));
    EXPECT_EQ(true, data[7].overlaps(3));
    EXPECT_EQ(false, data[7].overlaps(4));
    EXPECT_EQ(false, data[7].overlaps(5));
    EXPECT_EQ(true, data[7].overlaps(7));
    EXPECT_EQ(true, data[7].overlaps(8));

    EXPECT_EQ(1, data[0].value());
    EXPECT_EQ(2, data[1].value());
    EXPECT_EQ(6, data[5].value());
    EXPECT_EQ(9, data[8].value());
}

TEST(RegionTest, restrict_to_segment) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options();
    data[1] = solver::Options();
    data[2] = solver::Options();
    data[3] = solver::Options();
    data[4] = solver::Options();
    data[5] = solver::Options();
    data[6] = solver::Options();
    data[7] = solver::Options();
    data[8] = solver::Options();

    solver::Region region(std::array<solver::Options*, 9>{
        &data[0],
            & data[1],
            & data[2],
            & data[3],
            & data[4],
            & data[5],
            & data[6],
            & data[7],
            & data[8],
    });

    const solver::Options options(7);

    region.restrict_to_segment(1, options);
    for (size_t i = 0; i < 9; i++)
    {
        bool could_be_seven = i >= 3 && i < 6;
        EXPECT_EQ(could_be_seven, data[i].overlaps(options));
    }
}
