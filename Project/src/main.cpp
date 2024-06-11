#include <iostream>

#include <QApplication>
#include <QIcon>

#include "backsolver.h"
#include "gameLauncher.h"
#include "sudoku.h"
#include "sudokuGame.h"

int main(int argc, char *argv[]) {
	QApplication qtApp{argc, argv};

	SudokuGame game{};
	
	game.show();

	return qtApp.exec();
}