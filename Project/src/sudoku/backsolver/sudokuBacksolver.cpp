#include "backsolver.h"

SudokuBacksolver::SudokuBacksolver(SudokuMatrix &sudokuMatrix) : sudokuMatrix{sudokuMatrix} {}

SudokuMatrix SudokuBacksolver::solveMatrix() {
	SudokuMatrixMasked maskedMatrix{this->sudokuMatrix};

	std::vector<SudokuMatrixMasked> maskedMatrices;

	std::pair<int, int> startPosition{this->findEmptyPosition(maskedMatrix)};

	SudokuSubMatrix startPositionSubMatrix = *maskedMatrix.getSubMatrixAtCellPosition(startPosition);
	std::vector<int> startPositionSubMatrixValuesMissing = startPositionSubMatrix.getValuesMissing();
	std::vector<int> startPositionCrossValuesMissing = maskedMatrix.getCrossValuesMissingAtPosition(startPosition);

	
}

std::pair<int, int> SudokuBacksolver::findEmptyPosition(SudokuMatrixMasked &sudokuMatrixMasked) {
	std::pair<int, int> position{-1, -1};

	for (int i{0}; i < sudokuMatrixMasked.getSize(); i++) {
		for (int j{0}; i < sudokuMatrixMasked.getSize(); j++) {
			if (sudokuMatrixMasked.getCellAtPosition({i, j})->getValue() == 0) {
				position = {i, j};
				i = sudokuMatrixMasked.getSize();
				j = sudokuMatrixMasked.getSize();
			}
		}
	}

	return position;
}