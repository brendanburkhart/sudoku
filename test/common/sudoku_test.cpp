#include "../../src/common/sudoku.hpp"

#include "gtest/gtest.h"

TEST(SudokuTest, cell_accessors) {
    common::Sudoku puzzle;

    EXPECT_EQ(false, puzzle.get_cell(0, 0).has_value());
    puzzle.set_cell(0, 0, 5);
    EXPECT_EQ(true, puzzle.get_cell(0, 0).has_value());
    EXPECT_EQ(5, puzzle.get_cell(0, 0).value());

    EXPECT_EQ(false, puzzle.get_cell(7, 3).has_value());
    puzzle.set_cell(7, 3, 2);
    EXPECT_EQ(true, puzzle.get_cell(7, 3).has_value());
    EXPECT_EQ(2, puzzle.get_cell(7, 3).value());

    EXPECT_EQ(false, puzzle.get_cell(2, 8).has_value());
    puzzle.set_cell(2, 8, 9);
    EXPECT_EQ(true, puzzle.get_cell(2, 8).has_value());
    EXPECT_EQ(9, puzzle.get_cell(2, 8).value());

    EXPECT_EQ(false, puzzle.get_cell(6, 5).has_value());
    puzzle.set_cell(6, 5, 1);
    EXPECT_EQ(true, puzzle.get_cell(6, 5).has_value());
    EXPECT_EQ(1, puzzle.get_cell(6, 5).value());

    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            puzzle.set_cell(i, j, i * 9 + j + 1);
        }
    }

    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            auto value = puzzle.get_cell(i, j);
            EXPECT_EQ(true, value.has_value());
            EXPECT_EQ(i * 9 + j + 1, value.value());
        }
    }
}

TEST(SudokuTest, is_empty) {
    common::Sudoku puzzle;

    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            EXPECT_EQ(false, puzzle.get_cell(i, j).has_value());
        }
    }
}

TEST(SudokuTest, not_valid_box) {
    common::Sudoku puzzle;

    puzzle.set_cell(6, 6, 4);
    puzzle.set_cell(7, 7, 4);

    EXPECT_EQ(false, puzzle.is_valid());
}

TEST(SudokuTest, not_valid_column) {
    common::Sudoku puzzle;

    puzzle.set_cell(2, 7, 4);
    puzzle.set_cell(7, 7, 4);

    EXPECT_EQ(false, puzzle.is_valid());
}

TEST(SudokuTest, not_valid_row) {
    common::Sudoku puzzle;

    puzzle.set_cell(7, 0, 4);
    puzzle.set_cell(7, 3, 4);

    EXPECT_EQ(false, puzzle.is_valid());
}

void construct_puzzle(common::Sudoku& puzzle) {
    puzzle.set_cell(0, 0, 1);
    puzzle.set_cell(0, 1, 2);
    puzzle.set_cell(0, 2, 3);
    puzzle.set_cell(0, 3, 4);
    puzzle.set_cell(0, 4, 5);
    puzzle.set_cell(0, 5, 6);
    puzzle.set_cell(0, 6, 7);
    puzzle.set_cell(0, 7, 8);
    puzzle.set_cell(0, 8, 9);

    puzzle.set_cell(1, 0, 4);
    puzzle.set_cell(1, 1, 5);
    puzzle.set_cell(1, 2, 6);
    puzzle.set_cell(1, 3, 7);
    puzzle.set_cell(1, 4, 8);
    puzzle.set_cell(1, 5, 9);
    puzzle.set_cell(1, 6, 1);
    puzzle.set_cell(1, 7, 2);
    puzzle.set_cell(1, 8, 3);

    puzzle.set_cell(2, 0, 7);
    puzzle.set_cell(2, 1, 8);
    puzzle.set_cell(2, 2, 9);
    puzzle.set_cell(2, 3, 1);
    puzzle.set_cell(2, 4, 2);
    puzzle.set_cell(2, 5, 3);
    puzzle.set_cell(2, 6, 4);
    puzzle.set_cell(2, 7, 5);
    puzzle.set_cell(2, 8, 6);
}

void construct_solution(common::Sudoku& puzzle) {
    puzzle.set_cell(0, 0, 1);
    puzzle.set_cell(0, 1, 2);
    puzzle.set_cell(0, 2, 3);
    puzzle.set_cell(0, 3, 4);
    puzzle.set_cell(0, 4, 5);
    puzzle.set_cell(0, 5, 6);
    puzzle.set_cell(0, 6, 7);
    puzzle.set_cell(0, 7, 8);
    puzzle.set_cell(0, 8, 9);

    puzzle.set_cell(1, 0, 4);
    puzzle.set_cell(1, 1, 5);
    puzzle.set_cell(1, 2, 6);
    puzzle.set_cell(1, 3, 7);
    puzzle.set_cell(1, 4, 8);
    puzzle.set_cell(1, 5, 9);
    puzzle.set_cell(1, 6, 1);
    puzzle.set_cell(1, 7, 2);
    puzzle.set_cell(1, 8, 3);

    puzzle.set_cell(2, 0, 7);
    puzzle.set_cell(2, 1, 8);
    puzzle.set_cell(2, 2, 9);
    puzzle.set_cell(2, 3, 1);
    puzzle.set_cell(2, 4, 2);
    puzzle.set_cell(2, 5, 3);
    puzzle.set_cell(2, 6, 4);
    puzzle.set_cell(2, 7, 5);
    puzzle.set_cell(2, 8, 6);

    puzzle.set_cell(3, 0, 2);
    puzzle.set_cell(3, 1, 3);
    puzzle.set_cell(3, 2, 1);
    puzzle.set_cell(3, 3, 5);
    puzzle.set_cell(3, 4, 6);
    puzzle.set_cell(3, 5, 4);
    puzzle.set_cell(3, 6, 8);
    puzzle.set_cell(3, 7, 9);
    puzzle.set_cell(3, 8, 7);

    puzzle.set_cell(4, 0, 5);
    puzzle.set_cell(4, 1, 6);
    puzzle.set_cell(4, 2, 4);
    puzzle.set_cell(4, 3, 8);
    puzzle.set_cell(4, 4, 9);
    puzzle.set_cell(4, 5, 7);
    puzzle.set_cell(4, 6, 2);
    puzzle.set_cell(4, 7, 3);
    puzzle.set_cell(4, 8, 1);

    puzzle.set_cell(5, 0, 8);
    puzzle.set_cell(5, 1, 9);
    puzzle.set_cell(5, 2, 7);
    puzzle.set_cell(5, 3, 2);
    puzzle.set_cell(5, 4, 3);
    puzzle.set_cell(5, 5, 1);
    puzzle.set_cell(5, 6, 5);
    puzzle.set_cell(5, 7, 6);
    puzzle.set_cell(5, 8, 4);

    puzzle.set_cell(6, 0, 3);
    puzzle.set_cell(6, 1, 1);
    puzzle.set_cell(6, 2, 2);
    puzzle.set_cell(6, 3, 6);
    puzzle.set_cell(6, 4, 4);
    puzzle.set_cell(6, 5, 5);
    puzzle.set_cell(6, 6, 9);
    puzzle.set_cell(6, 7, 7);
    puzzle.set_cell(6, 8, 8);

    puzzle.set_cell(7, 0, 6);
    puzzle.set_cell(7, 1, 4);
    puzzle.set_cell(7, 2, 5);
    puzzle.set_cell(7, 3, 9);
    puzzle.set_cell(7, 4, 7);
    puzzle.set_cell(7, 5, 8);
    puzzle.set_cell(7, 6, 3);
    puzzle.set_cell(7, 7, 1);
    puzzle.set_cell(7, 8, 2);

    puzzle.set_cell(8, 0, 9);
    puzzle.set_cell(8, 1, 7);
    puzzle.set_cell(8, 2, 8);
    puzzle.set_cell(8, 3, 3);
    puzzle.set_cell(8, 4, 1);
    puzzle.set_cell(8, 5, 2);
    puzzle.set_cell(8, 6, 6);
    puzzle.set_cell(8, 7, 4);
    puzzle.set_cell(8, 8, 5);
}

TEST(SudokuTest, is_valid) {
    common::Sudoku puzzle;
    construct_puzzle(puzzle);

    EXPECT_EQ(true, puzzle.is_valid());
}

TEST(SudokuTest, not_solved) {
    common::Sudoku puzzle;
    construct_puzzle(puzzle);

    EXPECT_EQ(false, puzzle.is_solved());
}

TEST(SudokuTest, is_solved) {
    common::Sudoku puzzle;
    construct_solution(puzzle);

    EXPECT_EQ(true, puzzle.is_solved());
}

TEST(SudokuTest, is_solution_to) {
    common::Sudoku puzzle;
    construct_puzzle(puzzle);

    common::Sudoku solution;
    construct_solution(solution);

    EXPECT_EQ(true, solution.is_solution_to(puzzle));
    EXPECT_EQ(true, solution.is_solution_to(solution));
    EXPECT_EQ(false, puzzle.is_solution_to(solution));
    EXPECT_EQ(false, puzzle.is_solution_to(puzzle));
}

