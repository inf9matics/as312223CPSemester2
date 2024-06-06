#include <iostream>

#include <QApplication>
#include <QIcon>

#include "backsolver.h"
#include "gameLauncher.h"
#include "sudoku.h"
#include "sudokuQt.h"

int main(int argc, char *argv[]) {
	QApplication qtApp{argc, argv};

	SudokuMatrixQt sudokuMatrixQt{};

	// GameLauncher gameLauncher{};
	// gameLauncher.show();

	sudokuMatrixQt.setValueAt({0, 0}, 1);
	sudokuMatrixQt.setValueAt({1, 0}, 2);
	sudokuMatrixQt.setValueAt({2, 0}, 3);
	sudokuMatrixQt.setValueAt({3, 0}, 4);
	sudokuMatrixQt.setValueAt({4, 0}, 5);
	sudokuMatrixQt.setValueAt({5, 0}, 6);
	sudokuMatrixQt.setValueAt({6, 0}, 7);
	sudokuMatrixQt.setValueAt({7, 0}, 8);
	sudokuMatrixQt.setValueAt({8, 0}, 9);

	sudokuMatrixQt.getCellAtPosition({0, 0})->addParityCell(sudokuMatrixQt.getCellAtPosition({3, 3}));
	sudokuMatrixQt.getCellAtPosition({1, 0})->lock();
	// sudokuMatrix.setValueAt({3, 0}, 2);

	// SudokuBacksolver backsolver{sudokuMatrix};
	// std::pair<bool, SudokuMatrix> solvedMatrix = backsolver.solveMatrix();

	sudokuMatrixQt.showBoard();

	return qtApp.exec();
	// return 0;
}