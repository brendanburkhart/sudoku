#include "../../src/solver/super_region.hpp"

#include "gtest/gtest.h"

std::array<solver::Options, 9> construct_data(const std::array<int, 9>& values) {
    return std::array<solver::Options, 9>({
        values[0],
        values[1],
        values[2],
        values[3],
        values[4],
        values[5],
        values[6],
        values[7],
        values[8],
    });
}

solver::Region construct_region(std::array<solver::Options, 9>& data) {
    std::array<solver::Options*, 9> members = {
        &data[0],
        &data[1],
        &data[2],
        &data[3],
        &data[4],
        &data[5],
        &data[6],
        &data[7],
        &data[8],
    };

    return solver::Region(members);
}

solver::SuperRegion construct_super_region(solver::Region& region1, solver::Region& region2, solver::Region& region3) {
    std::array<solver::Region*, 3> members = {
        &region1,
        &region2,
        &region3,
    };

    return solver::SuperRegion(members);
}

class SuperRegionTest : public ::testing::Test {
protected:
    SuperRegionTest()
        : data1(construct_data(values1)), data2(construct_data(values2)), data3(construct_data(values3)), 
          region1(construct_region(data1)), region2(construct_region(data2)), region3(construct_region(data3)),
          super_region(construct_super_region(region1, region2, region3)) { 
        region1.eliminate();
        region2.eliminate();
        region3.eliminate();
        region1.exclude();
        region2.exclude();
        region3.exclude();
    }

    static constexpr std::array<int, 9> values1 = { 1, 2, 3, solver::Options::all, 7, 9, 5, 6, solver::Options::all };
    static constexpr std::array<int, 9> values2 = { solver::Options::all, 5, 6, 2, 1, solver::Options::all, 3, 9, solver::Options::all };
    static constexpr std::array<int, 9> values3 = { solver::Options::all, solver::Options::all, solver::Options::all, 5, 6, 3, 1, 2, solver::Options::all };

    std::array<solver::Options, 9> data1;
    std::array<solver::Options, 9> data2;
    std::array<solver::Options, 9> data3;

    solver::Region region1;
    solver::Region region2;
    solver::Region region3;

    solver::SuperRegion super_region;
};

TEST_F(SuperRegionTest, restrict_between) {
    EXPECT_EQ(true, data2[8].overlaps(7));

    super_region.restrict_between(1);

    EXPECT_EQ(false, data2[8].overlaps(7));
}
