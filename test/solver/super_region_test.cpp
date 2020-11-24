#include "../../src/solver/super_region.hpp"

#include "gtest/gtest.h"

std::array<solver::Options, 9> construct_data() {
    solver::Options seven = solver::Options::from_value(7);
    solver::Options value = solver::Options::all();
    value.remove(seven);

    return std::array<solver::Options, 9>({
        value,
        value,
        value,
        value,
        value,
        value,
        value,
        value,
        value,
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
        : data1(construct_data()), data2(construct_data()), data3(construct_data()), 
          region1(construct_region(data1)), region2(construct_region(data2)), region3(construct_region(data3)),
          super_region(construct_super_region(region1, region2, region3)) {

        data2[3].add(solver::Options::from_value(7));
        data2[4].add(solver::Options::from_value(7));
        data2[5].add(solver::Options::from_value(7));
        data2[6].add(solver::Options::from_value(7));
        data3[6].add(solver::Options::from_value(7));

        region1.eliminate();
        region2.eliminate();
        region3.eliminate();
        region1.exclude();
        region2.exclude();
        region3.exclude();
    }

    std::array<solver::Options, 9> data1;
    std::array<solver::Options, 9> data2;
    std::array<solver::Options, 9> data3;

    solver::Region region1;
    solver::Region region2;
    solver::Region region3;

    solver::SuperRegion super_region;
};

TEST_F(SuperRegionTest, restrict_between) {
    EXPECT_EQ(true, data2[6].overlaps(solver::Options::from_value(7)));

    super_region.restrict_between(1);

    EXPECT_EQ(false, data2[6].overlaps(solver::Options::from_value(7)));
}
