#include <iostream>

#include <QApplication>

#include "backsolver.h"
#include "gameLauncher.h"
#include "sudoku.h"
// #include "sudokuQt.h"

int main(int argc, char *argv[]) {
	QApplication qtApp{argc, argv};

	SudokuMatrix sudokuMatrix{};

	sudokuMatrix.setValueAt({0, 0}, 1);
	sudokuMatrix.setValueAt({0, 1}, 2);
	sudokuMatrix.setValueAt({0, 2}, 3);
	sudokuMatrix.setValueAt({1, 0}, 4);
	sudokuMatrix.setValueAt({1, 1}, 5);
	sudokuMatrix.setValueAt({1, 2}, 6);
	sudokuMatrix.setValueAt({2, 0}, 7);
	sudokuMatrix.setValueAt({2, 1}, 8);
	sudokuMatrix.setValueAt({2, 2}, 9);

	// sudokuMatrix.getCellAtPosition({0, 0})->addParityCell(sudokuMatrix.getCellAtPosition({3, 0}));
	// sudokuMatrix.setValueAt({3, 0}, 2);

	SudokuBacksolver backsolver{sudokuMatrix};
	std::pair<bool, SudokuMatrix> solvedMatrix = backsolver.solveMatrix();

	GameLauncher gameLauncher{};
	gameLauncher.show();

	// return qtApp.exec();
	return 0;
}