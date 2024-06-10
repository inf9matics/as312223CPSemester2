#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include "gameLauncher.h"
#include "sudokuQt.h"

class SudokuGame : public Game, public SudokuMatrixQt {
    Q_OBJECT

    public:
    SudokuGame(GameWindow *gameWindow);

    ~SudokuGame();

    SudokuGame &operator=(const SudokuMatrixQt &sudokuMatrixQt);
};

#endif