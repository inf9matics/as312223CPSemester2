#include "backsolver.h"

SudokuBacksolver::SudokuBacksolver(SudokuMatrix *sudokuMatrix) : sudokuMatrix{sudokuMatrix} {}

std::pair<bool, SudokuMatrix> SudokuBacksolver::solveMatrix() {
	SudokuMatrixMasked maskedMatrix{*this->sudokuMatrix};

	std::pair<bool, SudokuMatrix *> recurseSolution = this->recurseSolveMatrix(maskedMatrix);
	if (recurseSolution.first) {
		*this->sudokuMatrix = *recurseSolution.second;
		delete recurseSolution.second;
	}
	return std::pair<bool, SudokuMatrix>{recurseSolution.first, *recurseSolution.second};
}

std::pair<bool, SudokuMatrix *> SudokuBacksolver::recurseSolveMatrix(SudokuMatrixMasked &sudokuMaskedMatrix) {
	std::pair<bool, SudokuMatrix *> solution;

	if (sudokuMaskedMatrix.getViable() && sudokuMaskedMatrix.getFilled()) {
		solution.first = true;
		SudokuMatrix *solutionMatrix = new SudokuMatrix{sudokuMaskedMatrix.getSudokuMatrix()};
		solution.second = solutionMatrix;

		return solution;
	} else {
		std::pair<int, int> emptyPosition = sudokuMaskedMatrix.findEmptyPosition();
		std::vector<int> missingValues = sudokuMaskedMatrix.getCellAtPosition(emptyPosition)->getMissingValues();
		solution.first = false;

		while (!missingValues.empty()) {
			std::vector<int>::iterator missingValuesIterator = missingValues.begin();
			std::advance(missingValuesIterator, std::rand() % missingValues.size());
			SudokuMatrixMasked recurseMatrix{sudokuMaskedMatrix};
			recurseMatrix.setValueAt(emptyPosition, *missingValuesIterator);
			std::pair<bool, SudokuMatrix *> recurseSolution = this->recurseSolveMatrix(recurseMatrix);
			if (recurseSolution.first) {
				return recurseSolution;
			}
			missingValues.erase(missingValuesIterator);
		}

		return solution;
	}

	return solution;
}