#include <cmath>

#include "sudoku.h"

SudokuMatrix::SudokuMatrix() {
	this->size = 9;
	this->subMatrixSize = 3;

	this->prepareCells()->prepareSubMatrices();
}

SudokuMatrix::SudokuMatrix(int subMatrixSize) {
	this->size = std::pow(size, 2);

	this->subMatrixSize = size;
}

SudokuMatrix::SudokuMatrix(const SudokuMatrix &sudokuMatrix) { *this = sudokuMatrix; }

SudokuMatrix::SudokuMatrix(SudokuMatrix &&sudokuMatrix) {
	this->size = sudokuMatrix.size;
	sudokuMatrix.size = -1;

	this->subMatrixSize = sudokuMatrix.subMatrixSize;
	sudokuMatrix.subMatrixSize = -1;

	this->cells.clear();
	this->cells = sudokuMatrix.cells;
	sudokuMatrix.cells.clear();
	std::vector<std::vector<SudokuCell>>::iterator cellsRowIterator = this->cells.begin();
	while (cellsRowIterator != this->cells.end()) {
		std::vector<SudokuCell>::iterator cellsColumnIterator = cellsRowIterator->begin();
		while (cellsColumnIterator != cellsRowIterator->end()) {
			cellsColumnIterator->setParent(this);
			cellsColumnIterator++;
		}
		cellsRowIterator++;
	}

	sudokuMatrix.subMatrices.clear();
	this->subMatrices.clear();
	this->prepareSubMatrices();

	sudokuMatrix.~SudokuMatrix();
}

SudokuMatrix &SudokuMatrix::operator=(const SudokuMatrix &sudokuMatrix) {
	this->size = sudokuMatrix.size;
	this->subMatrixSize = sudokuMatrix.subMatrixSize;

	this->cells.clear();
	this->cells = sudokuMatrix.cells;
	std::vector<std::vector<SudokuCell>>::iterator cellsRowIterator = this->cells.begin();
	while (cellsRowIterator != this->cells.end()) {
		std::vector<SudokuCell>::iterator cellsColumnIterator = cellsRowIterator->begin();
		while (cellsColumnIterator != cellsRowIterator->end()) {
			cellsColumnIterator->setParent(this);
			cellsColumnIterator++;
		}
		cellsRowIterator++;
	}

	this->subMatrices.clear();
	this->prepareSubMatrices();

	return *this;
}

SudokuMatrix *SudokuMatrix::prepareCells() {
	this->cells.reserve(this->size);
	for (int i{0}; i < this->size; i++) {
		this->cells.emplace_back();
		std::vector<SudokuCell> *row = &this->cells.at(i);
		row->reserve(this->size);
		for (int j{0}; j < this->size; j++) {
			row->emplace_back(std::pair<int, int>{i, j});
			row->back().setParent(this);
		}
	}
	return this;
}

SudokuMatrix *SudokuMatrix::prepareSubMatrices() {
	this->subMatrices.reserve(this->subMatrixSize);
	for (int i{0}; i < this->subMatrixSize; i++) {
		this->subMatrices.emplace_back();
		std::vector<SudokuSubMatrix> *row = &this->subMatrices.at(i);
		row->reserve(this->subMatrixSize);
		for (int j{0}; j < this->subMatrixSize; j++) {
			row->emplace_back(this->subMatrixSize, std::pair<int, int>{i, j}, this);
		}
	}
	return this;
}

int SudokuMatrix::getSize() { return this->size; }

int SudokuMatrix::getSubMatrixSize() { return this->subMatrixSize; }

SudokuCell *SudokuMatrix::setValueAt(std::pair<int, int> position, int value) {
	SudokuCell *cell = this->getCellAtPosition(position);
	if (value > this->size) {
		return cell;
	}
	return cell->setValue(value);
}

SudokuCell *SudokuMatrix::getCellAtPosition(std::pair<int, int> position) { return &this->cells.at(position.first).at(position.second); }

SudokuSubMatrix *SudokuMatrix::getSubMatrixAtPosition(std::pair<int, int> position) { return &this->subMatrices.at(position.first).at(position.second); }

SudokuSubMatrix *SudokuMatrix::getSubMatrixAtCellPosition(std::pair<int, int> position) {
	std::pair<int, int> subMatrixPosition{std::floor((position.first / this->subMatrixSize)), std::floor((position.second / this->subMatrixSize))};

	return this->getSubMatrixAtPosition(subMatrixPosition);
}

bool SudokuMatrix::checkViableAtPosition(std::pair<int, int> position) {
	for (int i{0}; i < this->size; i++) {
		if ((i != position.second) && (this->getCellAtPosition(position)->getValue() == this->getCellAtPosition({position.first, i})->getValue())) {
			return false;
		}
		if ((i != position.first) && (this->getCellAtPosition(position)->getValue() == this->getCellAtPosition({i, position.second})->getValue())) {
			return false;
		}
	}

	return this->getSubMatrixAtCellPosition(position)->checkIfViable();
}

SudokuMatrix *SudokuMatrix::updateSubMatrixAtCellPosition(std::pair<int, int> position) {
	this->getSubMatrixAtCellPosition(position)->updateExistingValues(this->getCellAtPosition(position)->getValue());

	return this;
}