#include <iostream>

#include <QApplication>
#include <QIcon>

#include "backsolver.h"
#include "gameLauncher.h"
#include "sudoku.h"
#include "sudokuQt.h"

int main(int argc, char *argv[]) {
	QApplication qtApp{argc, argv};

	SudokuMatrix sudokuMatrix{};

	// GameLauncher gameLauncher{};
	// gameLauncher.show();

	sudokuMatrix.setValueAt({0, 0}, 1);
	sudokuMatrix.setValueAt({1, 0}, 2);
	sudokuMatrix.setValueAt({2, 0}, 3);
	sudokuMatrix.setValueAt({3, 0}, 4);
	sudokuMatrix.setValueAt({4, 0}, 5);
	sudokuMatrix.setValueAt({5, 0}, 6);
	sudokuMatrix.setValueAt({6, 0}, 7);
	sudokuMatrix.setValueAt({7, 0}, 8);
	sudokuMatrix.setValueAt({8, 0}, 9);

	sudokuMatrix.getCellAtPosition({0, 0})->addParityCell(sudokuMatrix.getCellAtPosition({3, 0}));
	// sudokuMatrix.setValueAt({3, 0}, 2);

	// SudokuBacksolver backsolver{sudokuMatrix};
	// std::pair<bool, SudokuMatrix> solvedMatrix = backsolver.solveMatrix();

	SudokuMatrixQt sudokuMatrixQt{sudokuMatrix};
	sudokuMatrixQt.show();
	sudokuMatrixQt.showCells();

	return qtApp.exec();
	// return 0;
}