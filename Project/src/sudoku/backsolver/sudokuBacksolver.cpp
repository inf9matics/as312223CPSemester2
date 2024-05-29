#include "backsolver.h"

SudokuBacksolver::SudokuBacksolver(SudokuMatrix &sudokuMatrix) : sudokuMatrix{sudokuMatrix} {}

std::pair<bool, SudokuMatrix> SudokuBacksolver::solveMatrix() {
	SudokuMatrixMasked maskedMatrix{this->sudokuMatrix};

	std::vector<SudokuMatrixMasked> maskedMatrices;

	std::pair<int, int> startPosition{maskedMatrix.findEmptyPosition()};

	std::vector<int> startPositionValuesMissing = maskedMatrix.getCellAtPosition(startPosition)->getMissingValues();

	std::vector<int>::iterator startPositionValuesMissingIterator = startPositionValuesMissing.begin();
	while (startPositionValuesMissingIterator != startPositionValuesMissing.end()) {
		maskedMatrices.emplace_back(maskedMatrix);
		maskedMatrices.back().setValueAt(startPosition, *startPositionValuesMissingIterator);

		startPositionValuesMissingIterator++;
	}

	std::pair<bool, SudokuMatrix> solvedMatrix = this->recurseSolveMatrix(maskedMatrices);

	return solvedMatrix;
}

std::pair<bool, SudokuMatrix> SudokuBacksolver::recurseSolveMatrix(std::vector<SudokuMatrixMasked> &sudokuMaskedMatrices) {
	std::vector<SudokuMatrixMasked> maskedMatrices;

	std::vector<SudokuMatrixMasked>::iterator sudokuMaskedMatricesIterator = sudokuMaskedMatrices.begin();
	while (sudokuMaskedMatricesIterator != sudokuMaskedMatrices.end()) {
		std::pair<int, int> emptyPosition{sudokuMaskedMatricesIterator->findEmptyPosition()};
		std::vector<int> missingValues = sudokuMaskedMatricesIterator->getCellAtPosition(emptyPosition)->getMissingValues();

		if (missingValues.empty()) {
			if (sudokuMaskedMatricesIterator->checkFilled() && sudokuMaskedMatricesIterator->getViable()) {
				return std::pair<bool, SudokuMatrix>{true, SudokuMatrix{*sudokuMaskedMatricesIterator}};
			} else {
				return std::pair<bool, SudokuMatrix>{false, SudokuMatrix{*sudokuMaskedMatricesIterator}};
			}
		}
		std::vector<int>::iterator missingValuesIterator = missingValues.begin();
		while (missingValuesIterator != missingValues.end()) {
			maskedMatrices.emplace_back(*sudokuMaskedMatricesIterator);
			maskedMatrices.back().setValueAt(emptyPosition, *missingValuesIterator);

			missingValuesIterator++;
		}

		sudokuMaskedMatricesIterator++;
	}

	return this->recurseSolveMatrix(maskedMatrices);
}