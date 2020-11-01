#pragma once

#include <iostream>

#include "options.hpp"

namespace solver {

class Cell {
public:
    Cell(int initial = 0);

    int get_value() const;
    int checksum() const;
    bool could_be(int value) const;

    void eliminate(Options available);
    void update();

    friend std::ostream& operator<<(std::ostream& output, const Cell& sudoku);

private:
    int value;
    Options options;
};

}
