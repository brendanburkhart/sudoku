#pragma once

#include <array>
#include <iostream>
#include <optional>

namespace common {

class Sudoku {
public:
    Sudoku();

    void set_cell(size_t i, size_t j, int value);
    std::optional<int> get_cell(size_t i, size_t j) const;

    bool is_valid() const;
    bool is_solved() const;
    bool is_solution_to(const Sudoku& puzzle) const;

    friend std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku);

private:
    std::array<std::array<int, 9>, 9> data;
};

}  // namespace common
