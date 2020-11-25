#include "../../src/solver/super_region.hpp"

#include "gtest/gtest.h"

#include "../../src/common/sudoku.hpp"
#include "../../src/solver/sudoku.hpp"

common::Sudoku construct_puzzle_1() {
    common::Sudoku puzzle;

    puzzle.set_cell(0, 0, 4);
    puzzle.set_cell(0, 7, 5);

    puzzle.set_cell(1, 4, 5);
    puzzle.set_cell(1, 5, 2);
    puzzle.set_cell(1, 6, 1);

    puzzle.set_cell(2, 3, 9);
    puzzle.set_cell(2, 8, 2);

    puzzle.set_cell(3, 0, 1);
    puzzle.set_cell(3, 2, 7);
    puzzle.set_cell(3, 3, 8);
    puzzle.set_cell(3, 8, 5);

    puzzle.set_cell(4, 3, 7);
    puzzle.set_cell(4, 7, 6);

    puzzle.set_cell(5, 4, 2);
    puzzle.set_cell(5, 8, 3);

    puzzle.set_cell(6, 3, 6);
    puzzle.set_cell(6, 7, 8);

    puzzle.set_cell(7, 0, 6);
    puzzle.set_cell(7, 4, 8);
    puzzle.set_cell(7, 7, 1);

    puzzle.set_cell(8, 1, 8);
    puzzle.set_cell(8, 3, 2);
    puzzle.set_cell(8, 4, 7);
    puzzle.set_cell(8, 5, 3);

    return puzzle;
}

common::Sudoku construct_puzzle_2() {
    common::Sudoku puzzle;

    puzzle.set_cell(0, 2, 9);
    puzzle.set_cell(0, 3, 3);
    puzzle.set_cell(0, 5, 7);
    puzzle.set_cell(0, 6, 4);
    puzzle.set_cell(0, 8, 6);

    puzzle.set_cell(1, 1, 4);
    puzzle.set_cell(1, 2, 5);
    puzzle.set_cell(1, 3, 1);
    puzzle.set_cell(1, 5, 9);
    puzzle.set_cell(1, 8, 3);

    puzzle.set_cell(2, 0, 6);
    puzzle.set_cell(2, 2, 7);
    puzzle.set_cell(2, 4, 2);
    puzzle.set_cell(2, 7, 5);

    puzzle.set_cell(3, 0, 9);
    puzzle.set_cell(3, 3, 5);
    puzzle.set_cell(3, 4, 3);
    puzzle.set_cell(3, 6, 8);

    puzzle.set_cell(4, 1, 8);
    puzzle.set_cell(4, 3, 2);
    puzzle.set_cell(4, 4, 9);
    puzzle.set_cell(4, 6, 5);
    puzzle.set_cell(4, 7, 3);

    puzzle.set_cell(5, 1, 1);
    puzzle.set_cell(5, 6, 9);
    puzzle.set_cell(5, 7, 4);
    puzzle.set_cell(5, 8, 2);

    puzzle.set_cell(6, 2, 8);
    puzzle.set_cell(6, 3, 6);
    puzzle.set_cell(6, 7, 1);
    puzzle.set_cell(6, 8, 5);

    puzzle.set_cell(7, 0, 2);
    puzzle.set_cell(7, 2, 4);
    puzzle.set_cell(7, 5, 5);
    puzzle.set_cell(7, 7, 9);

    puzzle.set_cell(8, 0, 7);
    puzzle.set_cell(8, 4, 8);
    puzzle.set_cell(8, 5, 3);

    return puzzle;
}

common::Sudoku construct_puzzle_3() {
    common::Sudoku puzzle;

    puzzle.set_cell(0, 0, 5);
    puzzle.set_cell(0, 4, 1);
    puzzle.set_cell(0, 5, 8);

    puzzle.set_cell(1, 0, 8);
    puzzle.set_cell(1, 3, 3);
    puzzle.set_cell(1, 4, 7);

    puzzle.set_cell(2, 1, 1);
    puzzle.set_cell(2, 6, 9);

    puzzle.set_cell(3, 5, 2);
    puzzle.set_cell(3, 8, 3);

    puzzle.set_cell(4, 1, 7);
    puzzle.set_cell(4, 4, 6);

    puzzle.set_cell(5, 3, 1);
    puzzle.set_cell(5, 7, 5);

    puzzle.set_cell(6, 2, 5);
    puzzle.set_cell(6, 7, 1);

    puzzle.set_cell(7, 0, 4);
    puzzle.set_cell(7, 6, 6);
    puzzle.set_cell(7, 7, 2);

    puzzle.set_cell(8, 0, 3);
    puzzle.set_cell(8, 1, 8);
    puzzle.set_cell(8, 6, 7);
    puzzle.set_cell(8, 7, 9);

    return puzzle;
}

common::Sudoku construct_puzzle_4() {
    common::Sudoku puzzle;

    puzzle.set_cell(0, 0, 2);
    puzzle.set_cell(0, 1, 9);
    puzzle.set_cell(0, 5, 4);
    puzzle.set_cell(0, 6, 8);
    puzzle.set_cell(0, 7, 3);

    puzzle.set_cell(1, 0, 7);
    puzzle.set_cell(1, 3, 3);
    puzzle.set_cell(1, 5, 5);
    puzzle.set_cell(1, 7, 2);
    puzzle.set_cell(1, 8, 1);

    puzzle.set_cell(2, 1, 1);
    puzzle.set_cell(2, 2, 6);
    puzzle.set_cell(2, 3, 7);
    puzzle.set_cell(2, 5, 8);
    puzzle.set_cell(2, 6, 4);

    puzzle.set_cell(3, 0, 6);
    puzzle.set_cell(3, 3, 8);
    puzzle.set_cell(3, 4, 7);
    puzzle.set_cell(3, 6, 1);
    puzzle.set_cell(3, 8, 3);

    puzzle.set_cell(4, 0, 1);
    puzzle.set_cell(4, 1, 4);
    puzzle.set_cell(4, 2, 8);
    puzzle.set_cell(4, 3, 2);

    puzzle.set_cell(5, 0, 9);
    puzzle.set_cell(5, 3, 1);
    puzzle.set_cell(5, 7, 8);

    puzzle.set_cell(6, 4, 3);
    puzzle.set_cell(6, 6, 7);
    puzzle.set_cell(6, 7, 9);
    puzzle.set_cell(6, 8, 4);

    puzzle.set_cell(7, 0, 5);
    puzzle.set_cell(7, 1, 2);
    puzzle.set_cell(7, 2, 9);
    puzzle.set_cell(7, 4, 6);

    puzzle.set_cell(8, 2, 7);
    puzzle.set_cell(8, 4, 8);
    puzzle.set_cell(8, 8, 5);

    return puzzle;
}

common::Sudoku construct_puzzle_5() {
    common::Sudoku puzzle;

    puzzle.set_cell(1, 0, 1);
    puzzle.set_cell(1, 2, 9);
    puzzle.set_cell(1, 8, 4);

    puzzle.set_cell(2, 1, 4);
    puzzle.set_cell(2, 4, 2);
    puzzle.set_cell(2, 6, 6);
    puzzle.set_cell(2, 8, 1);

    puzzle.set_cell(3, 2, 1);
    puzzle.set_cell(3, 5, 8);

    puzzle.set_cell(4, 1, 6);
    puzzle.set_cell(4, 4, 4);
    puzzle.set_cell(4, 8, 3);

    puzzle.set_cell(5, 0, 8);
    puzzle.set_cell(5, 3, 2);
    puzzle.set_cell(5, 5, 3);

    puzzle.set_cell(6, 6, 7);
    puzzle.set_cell(6, 7, 8);
    puzzle.set_cell(6, 8, 5);

    puzzle.set_cell(7, 0, 9);
    puzzle.set_cell(7, 3, 7);
    puzzle.set_cell(7, 6, 4);
    puzzle.set_cell(7, 8, 6);

    puzzle.set_cell(8, 1, 2);
    puzzle.set_cell(8, 3, 8);
    puzzle.set_cell(8, 5, 6);

    return puzzle;
}

common::Sudoku construct_puzzle_6() {
    common::Sudoku puzzle;

    puzzle.set_cell(0, 0, 2);
    puzzle.set_cell(0, 3, 5);
    puzzle.set_cell(0, 7, 1);

    puzzle.set_cell(1, 1, 7);
    puzzle.set_cell(1, 5, 9);
    puzzle.set_cell(1, 7, 2);

    puzzle.set_cell(2, 3, 7);
    puzzle.set_cell(2, 6, 6);

    puzzle.set_cell(3, 1, 1);
    puzzle.set_cell(3, 2, 2);
    puzzle.set_cell(3, 7, 3);

    puzzle.set_cell(4, 2, 6);
    puzzle.set_cell(4, 4, 9);
    puzzle.set_cell(4, 5, 5);
    puzzle.set_cell(4, 7, 8);

    puzzle.set_cell(5, 1, 3);
    puzzle.set_cell(5, 3, 1);
    puzzle.set_cell(5, 5, 4);

    puzzle.set_cell(6, 1, 2);
    puzzle.set_cell(6, 2, 9);
    puzzle.set_cell(6, 7, 4);

    puzzle.set_cell(8, 0, 1);
    puzzle.set_cell(8, 1, 8);
    puzzle.set_cell(8, 2, 3);
    puzzle.set_cell(8, 5, 7);

    return puzzle;
}

TEST(SudokuTest, puzzle1) {
    common::Sudoku puzzle = construct_puzzle_1();

    solver::Sudoku sudoku = solver::Sudoku::construct(puzzle);
    sudoku.solve();
    common::Sudoku solution = sudoku.solution();

    EXPECT_EQ(true, solution.is_solved());
    EXPECT_EQ(true, solution.is_solution_to(puzzle));
}

TEST(SudokuTest, puzzle2) {
    common::Sudoku puzzle = construct_puzzle_2();

    solver::Sudoku sudoku = solver::Sudoku::construct(puzzle);
    sudoku.solve();
    common::Sudoku solution = sudoku.solution();

    EXPECT_EQ(true, solution.is_solved());
    EXPECT_EQ(true, solution.is_solution_to(puzzle));
}

TEST(SudokuTest, puzzle3) {
    common::Sudoku puzzle = construct_puzzle_3();

    solver::Sudoku sudoku = solver::Sudoku::construct(puzzle);
    sudoku.solve();
    common::Sudoku solution = sudoku.solution();

    EXPECT_EQ(true, solution.is_solved());
    EXPECT_EQ(true, solution.is_solution_to(puzzle));
}

TEST(SudokuTest, puzzle4) {
    common::Sudoku puzzle = construct_puzzle_4();

    solver::Sudoku sudoku = solver::Sudoku::construct(puzzle);
    sudoku.solve();
    common::Sudoku solution = sudoku.solution();

    EXPECT_EQ(true, solution.is_solved());
    EXPECT_EQ(true, solution.is_solution_to(puzzle));
}

TEST(SudokuTest, puzzle5) {
    common::Sudoku puzzle = construct_puzzle_5();

    solver::Sudoku sudoku = solver::Sudoku::construct(puzzle);
    sudoku.solve();
    common::Sudoku solution = sudoku.solution();

    EXPECT_EQ(true, solution.is_solved());
    EXPECT_EQ(true, solution.is_solution_to(puzzle));
}

TEST(SudokuTest, puzzle6) {
    common::Sudoku puzzle = construct_puzzle_6();

    solver::Sudoku sudoku = solver::Sudoku::construct(puzzle);
    sudoku.solve();
    common::Sudoku solution = sudoku.solution();

    EXPECT_EQ(true, solution.is_solved());
    EXPECT_EQ(true, solution.is_solution_to(puzzle));
}
