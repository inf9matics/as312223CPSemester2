#include <cmath>
#include <iostream>
#include <map>

#include "sudoku.h"

SudokuMatrix::SudokuMatrix(int size) {
	this->size = size;

	if (std::pow(((int)std::sqrt(this->size)), 2) != this->size) {
		throw std::invalid_argument("invalid_sudoku_matrix_size");
	}
	this->subMatrixSize = std::sqrt(this->size);

	this->cells.reserve(this->size);
	for (int i{0}; i < this->size; i++) {
		this->cells.emplace_back();
		std::vector<SudokuCell> *row = &this->cells.at(i);
		row->reserve(this->size);
		for (int j{0}; j < this->size; j++) {
			row->emplace_back(std::pair<int, int>{i, j}, *this);
		}
	}

	this->subMatrices.reserve(this->subMatrixSize);
	for (int i{0}; i < this->subMatrixSize; i++) {
		this->subMatrices.emplace_back();
		std::vector<SudokuSubMatrix> *row = &this->subMatrices.at(i);
		row->reserve(this->subMatrixSize);
		for (int j{0}; j < this->subMatrixSize; j++) {
			row->emplace_back(this->subMatrixSize, std::pair<int, int>{i, j}, *this);
		}
	}
}

SudokuCell &SudokuMatrix::setValueAt(std::pair<int, int> position, int value) {
	if (value > this->size) {
		return this->cells.at(position.first).at(position.second);
	}
	return this->getCellAtPosition(position).setValue(value);
}

SudokuCell &SudokuMatrix::getCellAtPosition(std::pair<int, int> position) { return this->cells.at(position.first).at(position.second); }

SudokuSubMatrix &SudokuMatrix::getSubMatrixAtPosition(std::pair<int, int> position) { return this->subMatrices.at(position.first).at(position.second); }

SudokuSubMatrix &SudokuMatrix::getSubMatrixAtCellPosition(std::pair<int, int> position) {
	std::pair<int, int> subMatrixPosition{std::floor((position.first / this->subMatrixSize)), std::floor((position.second / this->subMatrixSize))};

	return this->getSubMatrixAtPosition(subMatrixPosition);
}

bool SudokuMatrix::checkViableAtPosition(std::pair<int, int> position) {
	for (int i{0}; i < this->size; i++) {
		if ((i != position.second) && (this->getCellAtPosition(position).getValue() == this->getCellAtPosition({position.first, i}).getValue())) {
			return false;
		}
		if ((i != position.first) && (this->getCellAtPosition(position).getValue() == this->getCellAtPosition({i, position.second}).getValue())) {
			return false;
		}
	}

	return this->getSubMatrixAtCellPosition(position).checkIfViable();
}

SudokuSubMatrix::SudokuSubMatrix(int size, std::pair<int, int> position, SudokuMatrix &parentMatrix) {
	this->parentMatrix = &parentMatrix;

	this->size = size;
	this->position = position;

	this->cells.reserve(this->size);

	for (int i{0}; i < this->size; i++) {
		std::vector<SudokuCell *> row;
		row.reserve(this->size);
		for (int j{0}; j < this->size; j++) {
			row.emplace_back(&this->parentMatrix->getCellAtPosition({(this->position.first * this->size) + i, (this->position.second * this->size) + j}));
		}
		this->cells.push_back(row);
	}
}

bool SudokuSubMatrix::checkIfViable() {
	std::map<int, bool> existingValues;
	for (int i{0}; i < this->size; i++) {
		for (int j{0}; j < this->size; j++) {
			if (this->cells.at(i).at(j)->getValue() == 0) {
				continue;
			}
			if (existingValues.count(this->cells.at(i).at(j)->getValue()) == 0) {
				existingValues.insert({this->cells.at(i).at(j)->getValue(), true});
			} else {
				this->viable = false;
				this->filled = false;

				return false;
			}
		}
	}
	if (existingValues.size() == std::pow(this->size, 2)) {
		this->filled = true;
	}

	return true;
}

SudokuCell::SudokuCell(std::pair<int, int> position, SudokuMatrix &parentMatrix) {
	this->parentMatrix = &parentMatrix;

	this->position = position;

	this->parityCell = this;

	this->value = 0;
}

SudokuCell &SudokuCell::setValue(int value) {
	if (this->parityCell != this) {
		this->calledParity = true;
		if (!this->parityCell->getCalledParity()) {
			this->parityCell->setValue(value);
		}
		this->calledParity = false;
	}

	this->value = value;
	this->viable = this->parentMatrix->checkViableAtPosition(this->position);

	return *this;
}

SudokuCell &SudokuCell::setParityCell(SudokuCell &parityCell) {
	this->calledParity = true;
	this->parityCell = &parityCell;
	if (!this->parityCell->getCalledParity()) {
		this->parityCell->setParityCell(*this);
	}
	this->calledParity = false;

	return *this;
}

int SudokuCell::getValue() { return this->value; }

bool SudokuCell::getCalledParity() { return this->calledParity; }