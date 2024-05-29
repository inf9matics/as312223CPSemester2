#include <iostream>

#include <QApplication>

#include "backsolver.h"
#include "gameLauncher.h"
#include "sudoku.h"
#include "sudokuQt.h"

int main(int argc, char *argv[]) {
	QApplication qtApp{argc, argv};

	SudokuMatrixQt sudokuMatrixQt{};

	sudokuMatrixQt.setValueAt({0, 0}, 1);
	sudokuMatrixQt.setValueAt({0, 1}, 2);
	sudokuMatrixQt.setValueAt({0, 2}, 3);
	sudokuMatrixQt.setValueAt({1, 0}, 4);
	sudokuMatrixQt.setValueAt({1, 1}, 5);
	sudokuMatrixQt.setValueAt({1, 2}, 6);
	sudokuMatrixQt.setValueAt({2, 0}, 7);
	sudokuMatrixQt.setValueAt({2, 1}, 8);
	sudokuMatrixQt.setValueAt({2, 2}, 9);

	sudokuMatrixQt.getCellAtPosition({0, 0})->addParityCell(sudokuMatrixQt.getCellAtPosition({3, 0}));
	sudokuMatrixQt.setValueAt({3, 0}, 2);

	GameLauncher gameLauncher{};
	gameLauncher.show();

	return qtApp.exec();
}