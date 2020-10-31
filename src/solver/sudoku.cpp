#include "sudoku.hpp"

namespace solver {

Sudoku::Sudoku() {
    regions.reserve(3 * 9);

    // Construct row regions
    for (size_t i = 0; i < 9; i++)
    {
        std::array<Cell*, 9> members{
            &data[i][0],
            &data[i][1],
            &data[i][2],
            &data[i][3],
            &data[i][4],
            &data[i][5],
            &data[i][6],
            &data[i][7],
            &data[i][8],
        };

        regions.push_back(Region(members));
    }

    // Construct column regions
    for (size_t i = 0; i < 9; i++)
    {
        std::array<Cell*, 9> members{
            &data[0][i],
            &data[1][i],
            &data[2][i],
            &data[3][i],
            &data[4][i],
            &data[5][i],
            &data[6][i],
            &data[7][i],
            &data[8][i],
        };

        regions.push_back(Region(members));
    }

    // Construct box regions
    for (size_t j = 0; j < 3; j++) {
        for (size_t i = 0; i < 3; i++) {
            size_t row = j * 3;
            size_t column = i * 3;

            std::array<Cell*, 9> members{
                &data[row][column],
                &data[row][column + 1],
                &data[row][column + 2],
                &data[row + 1][column],
                &data[row + 1][column + 1],
                &data[row + 1][column + 2],
                &data[row + 2][column],
                &data[row + 2][column + 1],
                &data[row + 2][column + 2],
            };

            regions.push_back(Region(members));
        }
    }
}

void Sudoku::set_cell(size_t i, size_t j, int value) {
    data[i][j] = Cell(value);
}

Cell& Sudoku::get_cell(size_t i, size_t j) {
    return data[i][j];
}

void Sudoku::eliminate() {
    for (auto& region : regions) {
        region.eliminate();
    }

    for (auto& region : regions) {
        region.exclude();
    }
}

void Sudoku::update() {
    for (auto& row : data) {
        for (auto& cell : row) {
            cell.update();
        }
    }
}

std::ostream& operator<<(std::ostream& output, const Sudoku& sudoku) {
    for (auto& row : sudoku.data) {
        for (auto& cell : row) {
            output << cell << ", ";
        }

        output << "\n";
    }

    return output << std::endl;
}

}
