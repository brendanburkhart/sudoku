#include <chrono>
#include <iostream>
#include <optional>

#include "solver/sudoku.hpp"
#include "vision/vision.hpp"

int main() {
    vision::Vision vision;

    bool ok = vision.init();
    if (!ok) {
        std::cout << "Failed to initialize frame" << std::endl;
        return 0;
    }

    while (true) {
        ok = vision.capture_frame();
        if (!ok) {
            std::cout << "Failed to capture frame" << std::endl;
            return 0;
        }

        std::optional<common::Sudoku> grid_puzzle = vision.extract_puzzle();
        if (grid_puzzle) {
            common::Sudoku puzzle = grid_puzzle.value();

            solver::Sudoku solver = solver::Sudoku::construct(puzzle);
            solver.solve();
            common::Sudoku solution = solver.solution();

            if (solution.is_solution_to(puzzle)) {
                vision.add_solution(puzzle, solution);
            }
        }

        ok = vision.display_solution();
        if (!ok) {
            std::cout << "Exiting..." << std::endl;
            return 0;
        }
    }
}
