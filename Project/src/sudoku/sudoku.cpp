#include <cmath>
#include <iostream>
#include <map>

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

	this->cells = sudokuMatrix.cells;
	sudokuMatrix.cells.clear();
	std::vector<std::vector<SudokuCell>>::iterator cellsColumnIterator = this->cells.begin();
	while(cellsColumnIterator != this->cells.end()) {
		std::vector<SudokuCell>::iterator cellsRowIterator = cellsColumnIterator->begin();
		while(cellsRowIterator != cellsColumnIterator->end()) {
			cellsRowIterator->setParent(this);
			cellsRowIterator++;
		}
		cellsColumnIterator++;
	}

	sudokuMatrix.subMatrices.clear();
	this->subMatrices.clear();
	this->prepareSubMatrices();

	sudokuMatrix.~SudokuMatrix();
}

SudokuMatrix &SudokuMatrix::operator=(const SudokuMatrix &sudokuMatrix) {
	this->size = sudokuMatrix.size;
	this->subMatrixSize = sudokuMatrix.subMatrixSize;

	this->cells = sudokuMatrix.cells;
	std::vector<std::vector<SudokuCell>>::iterator cellsRowIterator = this->cells.begin();
	while (cellsRowIterator != this->cells.end()) {
		std::vector<SudokuCell>::iterator cellsColumnIterator = cellsRowIterator->begin();
		while (cellsColumnIterator != cellsRowIterator->end()) {
			cellsColumnIterator->setParent(this);

			std::vector<SudokuCell *>::iterator parityCellsIterator = cellsColumnIterator->parityCells.begin();
			while (parityCellsIterator != cellsColumnIterator->parityCells.end()) {
				*parityCellsIterator = this->getCellAtPosition((*parityCellsIterator)->position);
				parityCellsIterator++;
			}

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

SudokuSubMatrix::SudokuSubMatrix(int size, std::pair<int, int> position, SudokuMatrix *parentMatrix) {
	this->setParent(parentMatrix);

	this->size = size;
	this->position = position;

	this->cells.reserve(this->size);

	for (int i{0}; i < this->size; i++) {
		std::vector<SudokuCell *> row;
		row.reserve(this->size);
		for (int j{0}; j < this->size; j++) {
			row.emplace_back(this->parentMatrix->getCellAtPosition({(this->position.first * this->size) + i, (this->position.second * this->size) + j}));
		}
		this->cells.push_back(row);
	}
}

SudokuSubMatrix *SudokuSubMatrix::setParent(SudokuMatrix *parentMatrix) {
	this->parentMatrix = parentMatrix;
	return this;
}

SudokuMatrix *SudokuSubMatrix::getParent() { return this->parentMatrix; }

int SudokuSubMatrix::getSize() { return this->size; }

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

SudokuCell::SudokuCell(std::pair<int, int> position) {
	this->position = position;

	this->value = 0;
}

bool SudokuCell::operator==(SudokuCell &sudokuCell) { return ((this->parentMatrix == sudokuCell.parentMatrix) && (this->position == sudokuCell.position)); }

bool SudokuCell::operator!=(SudokuCell &sudokuCell) { return !(*this == sudokuCell); }

SudokuCell &SudokuCell::operator=(const SudokuCell &sudokuCell) {
	this->parentMatrix = sudokuCell.parentMatrix;
	
	this->parityCells.clear();
	this->parityCells = sudokuCell.parityCells;

	this->value = sudokuCell.value;

	this->position = sudokuCell.position;

	this->viable = this->parentMatrix->checkViableAtPosition(this->position);

	return *this;
}

SudokuCell *SudokuCell::setParent(SudokuMatrix *parentMatrix) {
	this->parentMatrix = parentMatrix;
	return this;
}

SudokuMatrix *SudokuCell::getParent() { return this->parentMatrix; }

SudokuCell *SudokuCell::setValue(int value) {
	this->value = value;
	this->viable = this->parentMatrix->checkViableAtPosition(this->position);

	if (!this->parityCells.empty()) {
		this->calledParity = true;
		std::vector<SudokuCell *>::iterator parityCellsIterator = this->parityCells.begin();
		while (parityCellsIterator != this->parityCells.end()) {
			if (!(*parityCellsIterator)->getCalledParity()) {
				(*parityCellsIterator)->setValue(value);
			}
			parityCellsIterator++;
		}
		this->calledParity = false;
	}

	return this;
}

int SudokuCell::getValue() { return this->value; }

bool SudokuCell::getCalledParity() { return this->calledParity; }

SudokuCell *SudokuCell::addParityCell(SudokuCell *parityCell) {
	this->parityCells.push_back(parityCell);

	this->calledParity = true;
	if (!parityCell->getCalledParity()) {
		parityCell->addParityCell(this);
	}
	this->calledParity = false;

	return this;
}

SudokuCell *SudokuCell::copyParityFrom(SudokuCell &sudokuCell) {
	std::vector<SudokuCell *>::iterator parityCellsIterator = sudokuCell.parityCells.begin();
	this->parityCells.clear();
	while (parityCellsIterator != sudokuCell.parityCells.end()) {
		this->parityCells.push_back(this->parentMatrix->getCellAtPosition((*parityCellsIterator)->position));
		parityCellsIterator++;
	}

	return this;
}

SudokuCell *SudokuCell::copyParityTo(SudokuCell &sudokuCell) {
	std::vector<SudokuCell *>::iterator parityCellsIterator = this->parityCells.begin();
	sudokuCell.parityCells.clear();
	while (parityCellsIterator != sudokuCell.parityCells.end()) {
		sudokuCell.parityCells.push_back(sudokuCell.parentMatrix->getCellAtPosition((*parityCellsIterator)->position));
		parityCellsIterator++;
	}

	return this;
}