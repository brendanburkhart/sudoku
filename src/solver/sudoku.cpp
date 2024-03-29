#include "sudoku.hpp"

namespace solver {

void Sudoku::construct_regions() {
    regions.reserve(3 * 9);

    // Construct row regions
    for (size_t i = 0; i < 9; i++) {
        std::array<Options*, 9> members{
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
    for (size_t i = 0; i < 9; i++) {
        std::array<Options*, 9> members{
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

            std::array<Options*, 9> members{
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

    // Construct super regions
    for (size_t i = 0; i < 3; i++) {
        std::array<Region*, 3> horizontal_regions{
            &regions[(i * 3)],
            &regions[(i * 3) + 1],
            &regions[(i * 3) + 2],
        };

        super_regions.push_back(SuperRegion(horizontal_regions));

        std::array<Region*, 3> vertical_regions{
            &regions[9 + (i * 3)],
            &regions[9 + (i * 3) + 1],
            &regions[9 + (i * 3) + 2],
        };

        super_regions.push_back(SuperRegion(vertical_regions));
    }
}

Sudoku::Sudoku() {
    construct_regions();
}

Sudoku::Sudoku(const Sudoku& sudoku) noexcept : data(sudoku.data) {
    construct_regions();
}

Sudoku::Sudoku(Sudoku&& sudoku) noexcept : data(std::move(sudoku.data)) {
    construct_regions();
}

Sudoku Sudoku::construct(const common::Sudoku& puzzle) {
    Sudoku sudoku;

    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (puzzle.get_cell(i, j).has_value()) {
                auto value = Options::from_value(puzzle.get_cell(i, j).value());
                sudoku.data[i][j] = value;
            }
        }
    }

    return sudoku;
}

// Extract solution after solving
common::Sudoku Sudoku::solution() {
    common::Sudoku solution;

    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            solution.set_cell(i, j, data[i][j].value());
        }
    }

    return solution;
}

void Sudoku::solve() {
    while (true) {
        int current_checksum = checksum();

        eliminate();

        for (auto& region : regions) {
            region.exclude();

            eliminate();
        }

        for (auto& super_region : super_regions) {
            for (int j = 0; j < 3; j++) {
                super_region.restrict_between(j);

                eliminate();
            }
        }

        for (auto& super_region : super_regions) {
            for (int j = 0; j < 3; j++) {
                super_region.restrict_within(j);

                eliminate();
            }
        }

        int new_checksum = checksum();
        if (new_checksum == solved_checksum || new_checksum == current_checksum) {
            break;
        }
    }
}

// Eliminates each region until no more elimination can be done
void Sudoku::eliminate() {
    while (true) {
        int current_checksum = checksum();

        for (auto& region : regions) {
            region.eliminate();
        }

        if (checksum() == current_checksum) {
            break;
        }
    }
}

// Checksum which monotonically decreases as puzzle is solved
// Equal to Sudoku::solved_checksum when solved.
int Sudoku::checksum() {
    int value = 0;

    for (auto& row : data) {
        for (auto& cell : row) {
            value += cell.checksum();
        }
    }

    return value;
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

}  // namespace solver
