#include "sudoku.h"

SudokuMatrix::SudokuMatrix(int size) {
	this->size = size;
	for (int i{0}; i < this->size; i++) {
		std::vector<SudokuCell> row;
		for (int j{0}; j < this->size; j++) {
			SudokuCell cell{std::pair<int, int>{i, j}, *this};
			row.push_back(cell);
		}
		this->cells.push_back(row);
	}
}

SudokuCell &SudokuMatrix::setValueAt(std::pair<int, int> position, int value) {
	if (value > this->size) {
		return this->cells.at(position.first).at(position.second);
	}
	return this->cells.at(position.first).at(position.second).setValue(value, *this);
}

SudokuCell &SudokuMatrix::getAtPosition(std::pair<int, int> position) { return this->cells.at(position.first).at(position.second); }

bool SudokuCell::checkIfViable(SudokuMatrix &matrix) {
	this->viable = true;

	for (int i{0}; i < matrix.size; i++) {
		if (this->value == matrix.getAtPosition(std::pair<int, int>{this->position.first, i}).value) {
			if (this->position != matrix.getAtPosition(std::pair<int, int>{this->position.first, i}).position) {
                this->viable = false;
			}
		}

		if (this->value == matrix.getAtPosition(std::pair<int, int>{i, this->position.second}).value) {
			if (this->position != matrix.getAtPosition(std::pair<int, int>{i, this->position.second}).position) {
                this->viable = false;
			}
		}
	}

    return this->viable;
}

SudokuCell::SudokuCell(std::pair<int, int> position, SudokuMatrix &matrix) {
	this->position = position;
	this->value = 0;
}

SudokuCell &SudokuCell::setValue(int value, SudokuMatrix &matrix) {
	this->value = value;
	this->checkIfViable(matrix);
	return *this;
}
