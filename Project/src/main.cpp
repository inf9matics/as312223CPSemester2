#include <iostream>

#include <QApplication>
#include <QIcon>

#include "backsolver.h"
#include "gameLauncher.h"
#include "sudoku.h"
#include "sudokuGame.h"

int main(int argc, char *argv[]) {
	QApplication qtApp{argc, argv};

	SudokuMatrixQt *sudokuBoard = new SudokuMatrixQt{};
	sudokuBoard->getCellAtPosition({0, 0})->addParityCell({3, 3});

	SudokuGame game{sudokuBoard};
	
	game.showGameLauncher();

	return qtApp.exec();
}