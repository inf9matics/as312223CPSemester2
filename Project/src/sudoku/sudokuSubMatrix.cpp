#include <cmath>

#include "sudoku.h"

SudokuSubMatrix::SudokuSubMatrix(int size, std::pair<int, int> position, SudokuMatrix *parentMatrix) : size(size), position(position), parentMatrix(parentMatrix) {
	for (int i{0}; i < this->size; i++) {
		for (int j{0}; j < this->size; j++) {
			this->cells.insert({{i, j}, {(this->position.first * this->size) + j, (this->position.second * this->size) + i}});
		}
	}

	for (int i{0}; i <= std::pow(this->size, 2); i++) {
		this->existingValues.insert({i, 0});
	}
}

SudokuSubMatrix::SudokuSubMatrix(const SudokuSubMatrix &sudokuSubMatrix) : cells(sudokuSubMatrix.cells), size(sudokuSubMatrix.size), viable(sudokuSubMatrix.viable), filled(sudokuSubMatrix.filled), existingValues(sudokuSubMatrix.existingValues) {}

SudokuSubMatrix &SudokuSubMatrix::operator=(const SudokuSubMatrix &sudokuSubMatrix) {
	this->cells.clear();
	this->cells = sudokuSubMatrix.cells;

	this->size = sudokuSubMatrix.size;

	this->viable = sudokuSubMatrix.viable;
	this->filled = sudokuSubMatrix.filled;

	this->existingValues.clear();
	this->existingValues = sudokuSubMatrix.existingValues;

	return *this;
}

bool SudokuSubMatrix::getViable() { return this->viable; }

SudokuSubMatrix *SudokuSubMatrix::setParent(SudokuMatrix *parentMatrix) {
	this->parentMatrix = parentMatrix;
	return this;
}

SudokuMatrix *SudokuSubMatrix::getParent() { return this->parentMatrix; }

int SudokuSubMatrix::getSize() { return this->size; }

bool SudokuSubMatrix::checkIfViable() {
	bool viable{true};
	std::map<int, int>::iterator existingValuesIterator = this->existingValues.begin();
	while (existingValuesIterator != this->existingValues.end()) {
		if ((existingValuesIterator->first != 0) && (existingValuesIterator->second > 1)) {
			viable = false;
		}
		existingValuesIterator++;
	}

	this->viable = viable;

	return this->viable;
}

SudokuSubMatrix *SudokuSubMatrix::updateExistingValues(std::pair<int, int> position) {
	SudokuCell *currentCell = this->parentMatrix->getCellAtPosition(this->cells.at(position));
	if (currentCell->getValue() > 0) {
		this->existingValues.at(currentCell->getValue())++;
	}
	if (currentCell->getPreviousValue() > 0) {
		this->existingValues.at(currentCell->getPreviousValue())--;
	}

	return this;
}

std::vector<int> SudokuSubMatrix::getValuesMissing() {
	std::vector<int> valuesMissing;

	std::map<int, int>::iterator existingValuesIterator = this->existingValues.begin();
	while (existingValuesIterator != this->existingValues.end()) {
		if (existingValuesIterator->second == 0) {
			valuesMissing.push_back(existingValuesIterator->first);
		}
		existingValuesIterator++;
	}

	return valuesMissing;
}

std::map<int, int> SudokuSubMatrix::getExistingValues() { return this->existingValues; }

std::vector<int> SudokuSubMatrix::getValuesFilled() {
	std::vector<int> valuesFilled;

	std::map<int, int>::iterator existingValuesIterator = this->existingValues.begin();
	while (existingValuesIterator != this->existingValues.end()) {
		if (existingValuesIterator->second > 0) {
			valuesFilled.push_back(existingValuesIterator->first);
		}
		existingValuesIterator++;
	}

	return valuesFilled;
}