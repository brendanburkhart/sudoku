#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "cell.hpp"
#include "region.hpp"

namespace solver {

class Sudoku {
public:
    Sudoku();

    void set_cell(size_t i, size_t j, int value);
    Cell& get_cell(size_t i, size_t j);

    void eliminate();
    void update();

    friend std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku);

private:
    std::array<std::array<Cell, 9>, 9> data;
    std::vector<Region> regions;
};

}
