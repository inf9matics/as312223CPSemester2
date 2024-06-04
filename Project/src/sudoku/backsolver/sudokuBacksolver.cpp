#include "backsolver.h"

SudokuBacksolver::SudokuBacksolver(SudokuMatrix &sudokuMatrix) : sudokuMatrix{sudokuMatrix} {}

std::pair<bool, SudokuMatrix> SudokuBacksolver::solveMatrix() {
	SudokuMatrixMasked maskedMatrix{this->sudokuMatrix};

	std::pair<bool, SudokuMatrix *> recurseSolution = this->recurseSolveMatrix(maskedMatrix);
	return std::pair<bool, SudokuMatrix>{recurseSolution.first, *recurseSolution.second};
}

std::pair<bool, SudokuMatrix *> SudokuBacksolver::recurseSolveMatrix(SudokuMatrixMasked &sudokuMaskedMatrix) {
	std::pair<std::pair<int, int>, std::vector<int>> emptyPositionWithMissingValues = sudokuMaskedMatrix.findEmptyPositionWithMissingValues();
	std::pair<bool, SudokuMatrix *> solution;
	solution.first = false;
	std::vector<int>::iterator missingValuesIterator = emptyPositionWithMissingValues.second.begin();
	while (!solution.first && (missingValuesIterator != emptyPositionWithMissingValues.second.end())) {
		sudokuMaskedMatrix.setValueAt(emptyPositionWithMissingValues.first, *missingValuesIterator);
		if (sudokuMaskedMatrix.getFilled() && sudokuMaskedMatrix.getViable()) {
			solution.first = true;
			solution.second = new SudokuMatrix{sudokuMaskedMatrix.getSudokuMatrix()};
		} else {
			solution = this->recurseSolveMatrix(sudokuMaskedMatrix);
		}
		missingValuesIterator++;
	}

	return solution;
}