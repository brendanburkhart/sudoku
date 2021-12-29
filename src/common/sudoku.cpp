#include "sudoku.hpp"

#include <unordered_set>

namespace common {

Sudoku::Sudoku() : data() {
    for (auto& row : data) {
        row.fill(0);
    }
}

void Sudoku::set_cell(size_t i, size_t j, int value) {
    data[i][j] = value;
}

std::optional<int> Sudoku::get_cell(size_t i, size_t j) const {
    if (data[i][j]) {
        return std::optional<int>(data[i][j]);
    }

    return std::nullopt;
}

bool Sudoku::is_valid() const {
    std::unordered_set<int> row_values;
    std::unordered_set<int> column_values;
    std::unordered_set<int> box_values;

    for (size_t i = 0; i < 9; i++) {
        row_values.clear();
        column_values.clear();
        box_values.clear();

        for (size_t j = 0; j < 9; j++) {
            if (row_values.count(data[i][j]) != 0) {
                return false;
            } else if (data[i][j] != 0) {
                row_values.insert(data[i][j]);
            }

            if (column_values.count(data[j][i]) != 0) {
                return false;
            } else if (data[j][i] != 0) {
                column_values.insert(data[j][i]);
            }

            size_t box_i = 3 * (i / 3) + (j / 3);
            size_t box_j = 3 * (i % 3) + (j % 3);
            if (box_values.count(data[box_i][box_j]) != 0) {
                return false;
            } else if (data[box_i][box_j] != 0) {
                box_values.insert(data[box_i][box_j]);
            }
        }
    }

    return true;
}

bool Sudoku::is_solved() const {
    if (!is_valid()) {
        return false;
    }

    for (auto& row : data) {
        for (auto& cell : row) {
            if (cell == 0) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::is_solution_to(const Sudoku& puzzle) const {
    if (!is_solved()) {
        return false;
    }

    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (puzzle.data[i][j] != 0 && puzzle.data[i][j] != data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku) {
    for (auto& row : sudoku.data) {
        for (auto& cell : row) {
            if (cell != 0) {
                output << cell << ", ";
            } else {
                output << " , ";
            }
        }

        output << "\n";
    }

    return output << std::endl;
}

}  // namespace common
