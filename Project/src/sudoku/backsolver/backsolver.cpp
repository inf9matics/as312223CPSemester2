#include "backsolver.h"

SudokuMatrixMasked::SudokuMatrixMasked(SudokuMatrix sudokuMatrix) : SudokuMatrix(sudokuMatrix) {
    this->parentMatrix = &sudokuMatrix;

    this->root = true;

	this->cells = &sudokuMatrix.cells;

	for (int i{0}; i < this->size; i++) {
		std::vector<SudokuCell *> row;
		for (int j{0}; j < this->size; j++) {
			row.push_back(&this->cells->at(i).at(j));
		}
		this->cellsMasked.push_back(row);
	}
}

SudokuMatrixMasked::SudokuMatrixMasked(const SudokuMatrixMasked &sudokuMatrixMasked) : SudokuMatrix(*sudokuMatrixMasked.parentMatrix){
    this->cells = sudokuMatrixMasked.cells;

    this->cellsMasked = sudokuMatrixMasked.cellsMasked;

    this->root = false;

    this->parentMatrix = sudokuMatrixMasked.parentMatrix;
}

SudokuCell &SudokuMatrixMasked::getCellAtPosition(std::pair<int, int> position) { return *this->cellsMasked.at(position.first).at(position.second); }