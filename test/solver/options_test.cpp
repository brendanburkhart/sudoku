#include "../../src/solver/options.hpp"

#include <array>

#include "gtest/gtest.h"

TEST(OptionsTest, default_contains_all) {
    const solver::Options default;

    for (int n = 1; n <= 9; n++) {
        EXPECT_EQ(true, default.overlaps(solver::Options::from_value(n)));
    }
}

TEST(OptionsTest, all_contains_all) {
    const solver::Options all = solver::Options::all();

    for (int n = 1; n <= 9; n++) {
        EXPECT_EQ(true, all.overlaps(solver::Options::from_value(n)));
    }
}

TEST(OptionsTest, contains_single) {
    for (int n = 1; n <= 9; n++) {
        const solver::Options options(solver::Options::from_value(n));

        for (int m = 1; m <= 9; m++) {
            EXPECT_EQ(n == m, options.overlaps(solver::Options::from_value(m)));
        }
    }
}

TEST(OptionsTest, none_contains_none) {
    const solver::Options none = solver::Options::none();

    for (int n = 1; n <= 9; n++) {
        EXPECT_EQ(false, none.overlaps(solver::Options::from_value(n)));
    }
}

TEST(OptionsTest, solved_single) {
    const solver::Options all;
    EXPECT_EQ(false, all.is_solved());

    for (int n = 1; n <= 9; n++) {
        const solver::Options single(solver::Options::from_value(n));

        EXPECT_EQ(true, single.is_solved());
    }
}

TEST(OptionsTest, value_accessor) {
    const solver::Options all;
    EXPECT_EQ(0, all.value());

    for (int n = 1; n <= 9; n++) {
        const solver::Options options(solver::Options::from_value(n));

        EXPECT_EQ(n, options.value());
    }
}

TEST(OptionsTest, checksum_disordered_one) {
    int all = 0;
    std::array<int, 9> values{3, 1, 7, 5, 4, 9, 8, 2, 6};

    solver::Options options;

    for (int n : values) {
        int previous = options.checksum();
        options.remove(solver::Options::from_value(n));
        EXPECT_LT(options.checksum(), previous);

        all += solver::Options::from_value(n).checksum();
    }

    EXPECT_EQ(all, solver::Options().checksum());
}

TEST(OptionsTest, checksum_disordered_two) {
    int all = 0;
    std::array<int, 9> values{8, 3, 5, 6, 2, 1, 9, 4, 7};

    solver::Options options;

    for (int n : values) {
        int previous = options.checksum();
        options.remove(solver::Options::from_value(n));
        EXPECT_LT(options.checksum(), previous);

        all += solver::Options::from_value(n).checksum();
    }

    EXPECT_EQ(all, solver::Options().checksum());
}

TEST(OptionsTest, count_order_one) {
    int count = 9;
    std::array<int, 9> values{3, 1, 7, 5, 4, 9, 8, 2, 6};

    solver::Options options;

    for (int n : values) {
        EXPECT_EQ(count, options.count());
        options.remove(solver::Options::from_value(n));
        EXPECT_EQ(--count, options.count());

        EXPECT_EQ(1, solver::Options::from_value(n).count());
    }
}

TEST(OptionsTest, count_order_two) {
    int count = 9;
    std::array<int, 9> values{8, 3, 5, 6, 2, 1, 9, 4, 7};

    solver::Options options;

    for (int n : values) {
        EXPECT_EQ(count, options.count());
        options.remove(solver::Options::from_value(n));
        EXPECT_EQ(--count, options.count());

        EXPECT_EQ(1, solver::Options::from_value(n).count());
    }
}

TEST(OptionsTest, remove_ordered) {
    solver::Options options;

    for (int n = 1; n <= 8; n++) {
        EXPECT_EQ(false, options.is_solved());
        EXPECT_EQ(0, options.value());
        EXPECT_EQ(true, options.overlaps(solver::Options::from_value(n)));

        options.remove(solver::Options::from_value(n));

        EXPECT_EQ(false, options.overlaps(solver::Options::from_value(n)));
    }

    EXPECT_EQ(true, options.is_solved());
    EXPECT_EQ(9, options.value());
}

TEST(OptionsTest, remove_disordered) {
    std::array<int, 8> values{3, 1, 7, 4, 5, 9, 8, 2};

    solver::Options options;

    for (int n : values) {
        EXPECT_EQ(false, options.is_solved());
        EXPECT_EQ(0, options.value());
        EXPECT_EQ(true, options.overlaps(solver::Options::from_value(n)));

        options.remove(solver::Options::from_value(n));

        EXPECT_EQ(false, options.overlaps(solver::Options::from_value(n)));
    }

    EXPECT_EQ(true, options.is_solved());
    EXPECT_EQ(6, options.value());
}

TEST(OptionsTest, add) {
    std::array<int, 8> values{3, 1, 7, 4, 5, 9, 8, 2};

    solver::Options options = solver::Options::from_value(0);

    for (int n : values) {
        EXPECT_EQ(false, options.overlaps(solver::Options::from_value(n)));
        options.add(solver::Options::from_value(n));
        EXPECT_EQ(true, options.overlaps(solver::Options::from_value(n)));
    }
}

TEST(OptionsTest, restrict_to) {
    solver::Options options;
    options.remove(solver::Options::from_value(7));
    options.remove(solver::Options::from_value(3));
    options.remove(solver::Options::from_value(5));
    options.remove(solver::Options::from_value(2));

    solver::Options available;
    options.remove(solver::Options::from_value(1));
    options.remove(solver::Options::from_value(2));
    options.remove(solver::Options::from_value(4));
    options.remove(solver::Options::from_value(6));
    options.remove(solver::Options::from_value(9));

    options.restrict_to(available);

    for (int n = 1; n <= 9; n++) {
        EXPECT_EQ(n == 8, options.overlaps(solver::Options::from_value(n)));
    }

    EXPECT_EQ(true, options.is_solved());
    EXPECT_EQ(8, options.value());
}
