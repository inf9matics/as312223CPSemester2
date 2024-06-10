#include <iostream>

#include <QApplication>
#include <QIcon>

#include "backsolver.h"
#include "gameLauncher.h"
#include "sudoku.h"
#include "sudokuGame.h"

int main(int argc, char *argv[]) {
	QApplication qtApp{argc, argv};

	GameLauncher gameLauncher;

	SudokuMatrixQt sudokuMatrixQt{};

	gameLauncher.addGame(&sudokuMatrixQt);

	gameLauncher.show();

	return qtApp.exec();
}