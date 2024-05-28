#include "backsolver.h"

SudokuBacksolver::SudokuBacksolver(SudokuMatrix &sudokuMatrix) : sudokuMatrix{sudokuMatrix} {}

SudokuMatrix SudokuBacksolver::solveMatrix() {
	SudokuMatrixMasked maskedMatrix{this->sudokuMatrix};

	std::vector<SudokuMatrixMasked> maskedMatrices;

	std::pair<int, int> startPosition;
	for (int i{0}; i < maskedMatrix.getSize(); i++) {
		for (int j{0}; i < maskedMatrix.getSize(); j++) {
			if (maskedMatrix.getCellAtPosition({i, j})->getValue() == 0) {
				startPosition = {i, j};
				i = maskedMatrix.getSize();
				j = maskedMatrix.getSize();
			}
		}
	}

	SudokuSubMatrix startPositionSubMatrix = *maskedMatrix.getSubMatrixAtCellPosition(startPosition);
	std::vector<int> startPositionValuesMissing = startPositionSubMatrix.getValuesMissing();
	std::vector<int>::iterator startPositionValuesMissingIterator = startPositionValuesMissing.begin();
	while (startPositionValuesMissingIterator != startPositionValuesMissing.end()) {
		maskedMatrices.emplace_back(maskedMatrix);
		maskedMatrices.back().setValueAt(startPosition, *startPositionValuesMissingIterator);
		startPositionValuesMissingIterator++;
	}

	this->recurseMaskedMatrices(maskedMatrices);
}

SudokuMatrixMasked SudokuBacksolver::recurseMaskedMatrices(std::vector<SudokuMatrixMasked> &maskedMatrices) {}