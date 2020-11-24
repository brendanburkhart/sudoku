#include "../../src/solver/region.hpp"

#include "gtest/gtest.h"

TEST(RegionTest, available_in_segment) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options::from_value(1);
    data[1] = solver::Options::from_value(2);
    data[2] = solver::Options::from_value(3);
    data[3] = solver::Options::all();
    data[4] = solver::Options::all();
    data[5] = solver::Options::from_value(6);
    data[6] = solver::Options::from_value(7);
    data[7] = solver::Options::all();
    data[8] = solver::Options::from_value(9);

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
    EXPECT_EQ(true, second_segment.overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, second_segment.overlaps(solver::Options::from_value(5)));

    const solver::Options third_segment = region.available_in_segment(2);
    EXPECT_EQ(3, third_segment.count());
    EXPECT_EQ(true, third_segment.overlaps(solver::Options::from_value(8)));
}

TEST(RegionTest, is_solved) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options::from_value(6);
    data[1] = solver::Options::from_value(3);
    data[2] = solver::Options::from_value(8);
    data[3] = solver::Options::from_value(2);
    data[4] = solver::Options::from_value(1);
    data[5] = solver::Options::from_value(4);
    data[6] = solver::Options::from_value(9);
    data[7] = solver::Options::from_value(7);
    data[8] = solver::Options::from_value(5);

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

    EXPECT_EQ(true, region.is_solved());
}

TEST(RegionTest, has_duplicates) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options::from_value(6);
    data[1] = solver::Options::from_value(3);
    data[2] = solver::Options::from_value(6);
    data[3] = solver::Options::from_value(2);
    data[4] = solver::Options::from_value(1);
    data[5] = solver::Options::from_value(4);
    data[6] = solver::Options::from_value(9);
    data[7] = solver::Options::from_value(7);
    data[8] = solver::Options::from_value(5);

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

    EXPECT_EQ(false, region.is_solved());
}

TEST(RegionTest, missing_value) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options::from_value(6);
    data[1] = solver::Options::from_value(3);
    data[2] = solver::Options::none();
    data[3] = solver::Options::from_value(2);
    data[4] = solver::Options::from_value(1);
    data[5] = solver::Options::from_value(4);
    data[6] = solver::Options::from_value(9);
    data[7] = solver::Options::from_value(7);
    data[8] = solver::Options::from_value(5);

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

    EXPECT_EQ(false, region.is_solved());
}

TEST(RegionTest, elimination) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options::from_value(1);
    data[1] = solver::Options::from_value(2);
    data[2] = solver::Options::from_value(3);
    data[3] = solver::Options::all();
    data[4] = solver::Options::all();
    data[5] = solver::Options::from_value(6);
    data[6] = solver::Options::from_value(7);
    data[7] = solver::Options::all();
    data[8] = solver::Options::from_value(9);

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

            EXPECT_EQ(overlaps, data[i].overlaps(solver::Options::from_value(n)));
        }
    }
}

TEST(RegionTest, single_exclude) {
    std::array<solver::Options, 9> data;

    solver::Options available;
    available.remove(solver::Options::from_value(4));

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

    data[0] = solver::Options::from_value(1);
    data[1] = solver::Options::from_value(2);
    data[2] = solver::Options::from_value(3);
    data[3] = solver::Options::all();
    data[4] = solver::Options::all();
    data[5] = solver::Options::from_value(6);
    data[6] = solver::Options::from_value(7);
    data[7] = solver::Options::all();
    data[8] = solver::Options::from_value(9);

    data[4].restrict_to(available);
    data[7].restrict_to(available);

    EXPECT_EQ(true, data[3].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, data[3].overlaps(solver::Options::from_value(6)));
    EXPECT_EQ(true, data[3].overlaps(solver::Options::from_value(8)));

    region.exclude();

    EXPECT_EQ(true, data[3].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(false, data[3].overlaps(solver::Options::from_value(6)));
    EXPECT_EQ(false, data[3].overlaps(solver::Options::from_value(8)));

    EXPECT_EQ(1, data[0].value());
    EXPECT_EQ(2, data[1].value());
    EXPECT_EQ(3, data[2].value());
    EXPECT_EQ(4, data[3].value());
    EXPECT_EQ(6, data[5].value());
    EXPECT_EQ(7, data[6].value());
    EXPECT_EQ(9, data[8].value());
}

TEST(RegionTest, multi_exclude) {
    std::array<solver::Options, 9> data;

    data[0] = solver::Options::from_value(1);
    data[1] = solver::Options::from_value(2);
    data[2] = solver::Options::all();
    data[3] = solver::Options::all();
    data[4] = solver::Options::all();
    data[5] = solver::Options::from_value(6);
    data[6] = solver::Options::all();
    data[7] = solver::Options::all();
    data[8] = solver::Options::from_value(9);

    solver::Options available;
    available.remove(solver::Options::from_value(3));
    available.remove(solver::Options::from_value(7));
    available.remove(solver::Options::from_value(8));

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

    EXPECT_EQ(true, data[2].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(true, data[2].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, data[2].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(true, data[2].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(true, data[2].overlaps(solver::Options::from_value(8)));
    EXPECT_EQ(false, data[3].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(true, data[3].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, data[3].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(false, data[3].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(false, data[3].overlaps(solver::Options::from_value(8)));
    EXPECT_EQ(false, data[4].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(true, data[4].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, data[4].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(false, data[4].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(false, data[4].overlaps(solver::Options::from_value(8)));
    EXPECT_EQ(true, data[6].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(true, data[6].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, data[6].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(true, data[6].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(true, data[6].overlaps(solver::Options::from_value(8)));
    EXPECT_EQ(true, data[7].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(true, data[7].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, data[7].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(true, data[7].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(true, data[7].overlaps(solver::Options::from_value(8)));

    region.exclude();

    EXPECT_EQ(true, data[2].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(false, data[2].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(false, data[2].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(true, data[2].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(true, data[2].overlaps(solver::Options::from_value(8)));
    EXPECT_EQ(false, data[3].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(true, data[3].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, data[3].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(false, data[3].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(false, data[3].overlaps(solver::Options::from_value(8)));
    EXPECT_EQ(false, data[4].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(true, data[4].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(true, data[4].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(false, data[4].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(false, data[4].overlaps(solver::Options::from_value(8)));
    EXPECT_EQ(true, data[6].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(false, data[6].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(false, data[6].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(true, data[6].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(true, data[6].overlaps(solver::Options::from_value(8)));
    EXPECT_EQ(true, data[7].overlaps(solver::Options::from_value(3)));
    EXPECT_EQ(false, data[7].overlaps(solver::Options::from_value(4)));
    EXPECT_EQ(false, data[7].overlaps(solver::Options::from_value(5)));
    EXPECT_EQ(true, data[7].overlaps(solver::Options::from_value(7)));
    EXPECT_EQ(true, data[7].overlaps(solver::Options::from_value(8)));

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
        &data[1],
        &data[2],
        &data[3],
        &data[4],
        &data[5],
        &data[6],
        &data[7],
        &data[8],
    });

    const solver::Options options = solver::Options::from_value(7);

    region.restrict_to_segment(1, options);
    for (size_t i = 0; i < 9; i++)
    {
        bool could_be_seven = i >= 3 && i < 6;
        EXPECT_EQ(could_be_seven, data[i].overlaps(options));
    }
}

TEST(RegionTest, exclude_from_segment) {
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
        &data[1],
        &data[2],
        &data[3],
        &data[4],
        &data[5],
        &data[6],
        &data[7],
        &data[8],
    });

    const solver::Options options = solver::Options::from_value(7);

    region.exclude_from_segment(1, options);
    for (size_t i = 0; i < 9; i++)
    {
        bool could_be_seven = i < 3 || i >= 6;
        EXPECT_EQ(could_be_seven, data[i].overlaps(options));
    }
}
