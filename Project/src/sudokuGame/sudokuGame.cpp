#include "sudokuGame.h"

SudokuGame::~SudokuGame() {}

SudokuGame::SudokuGame(GameWindow *gameWindow) : Game(gameWindow) {}

SudokuGame &SudokuGame::operator=(const SudokuMatrixQt &sudokuMatrixQt) {
    *this = sudokuMatrixQt;

    return *this;
}