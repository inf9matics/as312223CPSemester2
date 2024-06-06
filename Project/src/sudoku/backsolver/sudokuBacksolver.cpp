#include "backsolver.h"

SudokuBacksolver::SudokuBacksolver(SudokuMatrix &sudokuMatrix) : sudokuMatrix{sudokuMatrix} {}

std::pair<bool, SudokuMatrix> SudokuBacksolver::solveMatrix() {
	SudokuMatrixMasked maskedMatrix{this->sudokuMatrix};

	std::pair<bool, SudokuMatrix *> recurseSolution = this->recurseSolveMatrix(maskedMatrix);
	return std::pair<bool, SudokuMatrix>{recurseSolution.first, *recurseSolution.second};
}

std::pair<bool, SudokuMatrix *> SudokuBacksolver::recurseSolveMatrix(SudokuMatrixMasked &sudokuMaskedMatrix) {
	std::pair<int, int> emptyPosition = sudokuMaskedMatrix.findEmptyPosition();
	std::vector<int> missingValues = sudokuMaskedMatrix.getCellAtPosition(emptyPosition)->getMissingValues();
	std::pair<bool, SudokuMatrix *> solution;

	if (emptyPosition != std::pair<int, int>{-1, -1} && missingValues.empty()) {
		solution.first = false;
		return solution;

	} else {
		std::vector<int>::iterator missingValuesIterator = missingValues.begin();
		while (missingValuesIterator != missingValues.end()) {
			sudokuMaskedMatrix.setValueAt(emptyPosition, *missingValuesIterator);
			if (sudokuMaskedMatrix.getViable() && sudokuMaskedMatrix.getFilled()) {
				solution.first = true;
				solution.second = new SudokuMatrix{sudokuMaskedMatrix.getSudokuMatrix()};
				return solution;
			} else {
				solution = this->recurseSolveMatrix({sudokuMaskedMatrix});
			}
			missingValuesIterator++;
		}

		solution.first = false;
		return solution;
	}
}