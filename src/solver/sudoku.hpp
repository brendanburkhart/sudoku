#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "options.hpp"
#include "region.hpp"
#include "super_region.hpp"

namespace solver {

class Sudoku {
public:
    Sudoku();

    void set_cell(size_t i, size_t j, int value);
    Options& get_cell(size_t i, size_t j);

    void solve();
    bool is_solved() const;

    friend std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku);

private:
    std::array<std::array<Options, 9>, 9> data;
    std::vector<Region> regions;
    std::vector<SuperRegion> super_regions;

    static constexpr int solved_checksum = 9 * Options::all;

    void eliminate();
    int checksum();
};

}
