#include <iostream>

#include <QApplication>
#include <QIcon>

#include "backsolver.h"
#include "gameLauncher.h"
#include "sudoku.h"
#include "sudokuGame.h"

int main(int argc, char *argv[]) {
	srand(time(NULL));

	QApplication qtApp{argc, argv};

	SudokuGame game{};
	game.showGameLauncher();

	return qtApp.exec();
}