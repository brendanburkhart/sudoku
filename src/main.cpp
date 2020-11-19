#include <chrono>
#include <iostream>

#include "solver/sudoku.hpp"

// 10/30/20 NYT hard
void construct_game_1(solver::Sudoku& game) {
    game.set_cell(0, 0, 4);
    game.set_cell(0, 7, 5);

    game.set_cell(1, 4, 5);
    game.set_cell(1, 5, 2);
    game.set_cell(1, 6, 1);

    game.set_cell(2, 3, 9);
    game.set_cell(2, 8, 2);

    game.set_cell(3, 0, 1);
    game.set_cell(3, 2, 7);
    game.set_cell(3, 3, 8);
    game.set_cell(3, 8, 5);

    game.set_cell(4, 3, 7);
    game.set_cell(4, 7, 6);

    game.set_cell(5, 4, 2);
    game.set_cell(5, 8, 3);

    game.set_cell(6, 3, 6);
    game.set_cell(6, 7, 8);

    game.set_cell(7, 0, 6);
    game.set_cell(7, 4, 8);
    game.set_cell(7, 7, 1);

    game.set_cell(8, 1, 8);
    game.set_cell(8, 3, 2);
    game.set_cell(8, 4, 7);
    game.set_cell(8, 5, 3);
}

// 10/31/20 NYT easy
void construct_game_2(solver::Sudoku& game) {
    game.set_cell(0, 2, 9);
    game.set_cell(0, 3, 3);
    game.set_cell(0, 5, 7);
    game.set_cell(0, 6, 4);
    game.set_cell(0, 8, 6);

    game.set_cell(1, 1, 4);
    game.set_cell(1, 2, 5);
    game.set_cell(1, 3, 1);
    game.set_cell(1, 5, 9);
    game.set_cell(1, 8, 3);

    game.set_cell(2, 0, 6);
    game.set_cell(2, 2, 7);
    game.set_cell(2, 4, 2);
    game.set_cell(2, 7, 5);

    game.set_cell(3, 0, 9);
    game.set_cell(3, 3, 5);
    game.set_cell(3, 4, 3);
    game.set_cell(3, 6, 8);

    game.set_cell(4, 1, 8);
    game.set_cell(4, 3, 2);
    game.set_cell(4, 4, 9);
    game.set_cell(4, 6, 5);
    game.set_cell(4, 7, 3);

    game.set_cell(5, 1, 1);
    game.set_cell(5, 6, 9);
    game.set_cell(5, 7, 4);
    game.set_cell(5, 8, 2);

    game.set_cell(6, 2, 8);
    game.set_cell(6, 3, 6);
    game.set_cell(6, 7, 1);
    game.set_cell(6, 8, 5);

    game.set_cell(7, 0, 2);
    game.set_cell(7, 2, 4);
    game.set_cell(7, 5, 5);
    game.set_cell(7, 7, 9);

    game.set_cell(8, 0, 7);
    game.set_cell(8, 4, 8);
    game.set_cell(8, 5, 3);
}

// 10/31/20 NYT medium
void construct_game_3(solver::Sudoku& game) {
    game.set_cell(0, 0, 5);
    game.set_cell(0, 4, 1);
    game.set_cell(0, 5, 8);

    game.set_cell(1, 0, 8);
    game.set_cell(1, 3, 3);
    game.set_cell(1, 4, 7);

    game.set_cell(2, 1, 1);
    game.set_cell(2, 6, 9);

    game.set_cell(3, 5, 2);
    game.set_cell(3, 8, 3);

    game.set_cell(4, 1, 7);
    game.set_cell(4, 4, 6);

    game.set_cell(5, 3, 1);
    game.set_cell(5, 7, 5);

    game.set_cell(6, 2, 5);
    game.set_cell(6, 7, 1);

    game.set_cell(7, 0, 4);
    game.set_cell(7, 6, 6);
    game.set_cell(7, 7, 2);

    game.set_cell(8, 0, 3);
    game.set_cell(8, 1, 8);
    game.set_cell(8, 6, 7);
    game.set_cell(8, 7, 9);
}

// 11 / 2 / 20 NYT easy
void construct_game_4(solver::Sudoku & game) {
    game.set_cell(0, 0, 2);
    game.set_cell(0, 1, 9);
    game.set_cell(0, 5, 4);
    game.set_cell(0, 6, 8);
    game.set_cell(0, 7, 3);

    game.set_cell(1, 0, 7);
    game.set_cell(1, 3, 3);
    game.set_cell(1, 5, 5);
    game.set_cell(1, 7, 2);
    game.set_cell(1, 8, 1);

    game.set_cell(2, 1, 1);
    game.set_cell(2, 2, 6);
    game.set_cell(2, 3, 7);
    game.set_cell(2, 5, 8);
    game.set_cell(2, 6, 4);

    game.set_cell(3, 0, 6);
    game.set_cell(3, 3, 8);
    game.set_cell(3, 4, 7);
    game.set_cell(3, 6, 1);
    game.set_cell(3, 8, 3);

    game.set_cell(4, 0, 1);
    game.set_cell(4, 1, 4);
    game.set_cell(4, 2, 8);
    game.set_cell(4, 3, 2);

    game.set_cell(5, 0, 9);
    game.set_cell(5, 3, 1);
    game.set_cell(5, 7, 8);

    game.set_cell(6, 4, 3);
    game.set_cell(6, 6, 7);
    game.set_cell(6, 7, 9);
    game.set_cell(6, 8, 4);

    game.set_cell(7, 0, 5);
    game.set_cell(7, 1, 2);
    game.set_cell(7, 2, 9);
    game.set_cell(7, 4, 6);

    game.set_cell(8, 2, 7);
    game.set_cell(8, 4, 8);
    game.set_cell(8, 8, 5);
}

// 11/2/20 NYT medium
void construct_game_5(solver::Sudoku& game) {
    game.set_cell(1, 0, 1);
    game.set_cell(1, 2, 9);
    game.set_cell(1, 8, 4);

    game.set_cell(2, 1, 4);
    game.set_cell(2, 4, 2);
    game.set_cell(2, 6, 6);
    game.set_cell(2, 8, 1);

    game.set_cell(3, 2, 1);
    game.set_cell(3, 5, 8);

    game.set_cell(4, 1, 6);
    game.set_cell(4, 4, 4);
    game.set_cell(4, 8, 3);

    game.set_cell(5, 0, 8);
    game.set_cell(5, 3, 2);
    game.set_cell(5, 5, 3);

    game.set_cell(6, 6, 7);
    game.set_cell(6, 7, 8);
    game.set_cell(6, 8, 5);

    game.set_cell(7, 0, 9);
    game.set_cell(7, 3, 7);
    game.set_cell(7, 6, 4);
    game.set_cell(7, 8, 6);

    game.set_cell(8, 1, 2);
    game.set_cell(8, 3, 8);
    game.set_cell(8, 5, 6);
}

// 11/2/20 NYT hard
void construct_game_6(solver::Sudoku& game) {
    game.set_cell(0, 0, 2);
    game.set_cell(0, 3, 5);
    game.set_cell(0, 7, 1);

    game.set_cell(1, 1, 7);
    game.set_cell(1, 5, 9);
    game.set_cell(1, 7, 2);

    game.set_cell(2, 3, 7);
    game.set_cell(2, 6, 6);

    game.set_cell(3, 1, 1);
    game.set_cell(3, 2, 2);
    game.set_cell(3, 7, 3);

    game.set_cell(4, 2, 6);
    game.set_cell(4, 4, 9);
    game.set_cell(4, 5, 5);
    game.set_cell(4, 7, 8);

    game.set_cell(5, 1, 3);
    game.set_cell(5, 3, 1);
    game.set_cell(5, 5, 4);

    game.set_cell(6, 1, 2);
    game.set_cell(6, 2, 9);
    game.set_cell(6, 7, 4);

    game.set_cell(8, 0, 1);
    game.set_cell(8, 1, 8);
    game.set_cell(8, 2, 3);
    game.set_cell(8, 5, 7);
}

// TODO: add validation
// TODO: bitset
// TODO: specialize to prevent conversion
// TODO: readme
// TODO: counted 
// TODO: cache solved values

int main() {
    std::vector<solver::Sudoku> games;

    for (size_t i = 0; i < 500000; i++) {
        games.push_back(solver::Sudoku());
        
        switch (i % 4)
        {
        case 0:
            construct_game_1(games[i]);
            break;
        case 1:
            construct_game_6(games[i]);
            break;
        case 2:
            construct_game_1(games[i]);
            break;
        case 3:
            construct_game_6(games[i]);
            break;
        default:
            break;
        }
    }

    typedef std::chrono::high_resolution_clock Clock;

    auto t1 = Clock::now();
    
    for (auto& game : games) {
        game.solve();
    }

    auto t2 = Clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms" << std::endl;
}
