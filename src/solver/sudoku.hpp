#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "../common/sudoku.hpp"
#include "options.hpp"
#include "region.hpp"
#include "super_region.hpp"

namespace solver {

class Sudoku {
public:
    Sudoku(const Sudoku& sudoku) noexcept;
    Sudoku(Sudoku&& sudoku) noexcept;

    static Sudoku construct(const common::Sudoku& puzzle);
    common::Sudoku solution();

    void solve();
    bool is_solved() const;

    friend std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku);

private:
    std::array<std::array<Options, 9>, 9> data;
    std::vector<Region> regions;
    std::vector<SuperRegion> super_regions;

    static constexpr int solved_checksum = 9 * Options::all().checksum();

    Sudoku();

    void eliminate();
    int checksum();

    void construct_regions();
};

}
