#include <cmath>

#include "sudoku.h"

SudokuMatrix::SudokuMatrix() {
	this->size = 9;
	this->subMatrixSize = 3;

	this->viable = false;
	this->filled = false;

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
	this->iterateOverCells([this](SudokuCell *sudokuCell) { sudokuCell->setParent(this); });

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
	this->iterateOverCells([this](SudokuCell *sudokuCell) { sudokuCell->setParent(this); });

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
	bool viable{true};
	for (int i{0}; i < this->size; i++) {
		if ((i != position.second) && (this->getCellAtPosition(position)->getValue() == this->getCellAtPosition({position.first, i})->getValue())) {
			viable = false;
		}
		if ((i != position.first) && (this->getCellAtPosition(position)->getValue() == this->getCellAtPosition({i, position.second})->getValue())) {
			viable = false;
		}
	}

	viable = viable && this->getSubMatrixAtCellPosition(position)->checkIfViable();

	this->viable = viable;

	return this->viable;
}

SudokuMatrix *SudokuMatrix::updateSubMatrixAtCellPosition(std::pair<int, int> position) {
	this->getSubMatrixAtCellPosition(position)->updateExistingValues({position.first % this->subMatrixSize, position.second % this->subMatrixSize});

	return this;
}

template <typename Function> SudokuMatrix *SudokuMatrix::iterateOverCells(Function function) {
	std::vector<std::vector<SudokuCell>>::iterator rowIterator = this->cells.begin();
	while (rowIterator != this->cells.end()) {
		std::vector<SudokuCell>::iterator columnIterator = rowIterator->begin();
		while (columnIterator != rowIterator->end()) {
			function(columnIterator.base());
			columnIterator++;
		}
		rowIterator++;
	}

	return this;
}

bool SudokuMatrix::checkViable() {
	this->iterateOverCells([](SudokuCell *sudokuCell) { sudokuCell->parentMatrix->checkViableAtPosition(sudokuCell->position); });
	return this->viable;
}

bool SudokuMatrix::getViable() { return this->viable; }

bool SudokuMatrix::checkFilled() {
	bool filled{true};
	this->iterateOverCells([&filled](SudokuCell *sudokuCell) {
		if (!filled && sudokuCell->getValue() > 0) {
			filled = false;
		}
	});

	this->filled = filled;
	return this->filled;
}

bool SudokuMatrix::getFilled() { return this->filled; }

std::vector<int> SudokuMatrix::getCrossValuesPresentAtPosition(std::pair<int, int> position) {
	std::vector<int> valuesPresent;
	for(int i{0}; i<this->getSize(); i++) {
		valuesPresent.push_back(0);
	}

	for (int i{0}; i < this->size; i++) {
		if (position != std::pair<int, int>{i, i}) {
			valuesPresent.at(i)++;
		}
	}
	
	return valuesPresent;
}

std::vector<int> SudokuMatrix::getCrossValuesMissingAtPosition(std::pair<int, int> position) {
	std::vector<int> valuesPresent = this->getCrossValuesPresentAtPosition(position);

	std::vector<int> valuesMissing;
	std::vector<int>::iterator valuesPresentIterator = valuesPresent.begin();
	while(valuesPresentIterator != valuesPresent.end()) {
		if(*valuesPresentIterator == 0) {
			valuesMissing.push_back(*valuesPresentIterator);
		}
		valuesPresentIterator++;
	}

	return valuesMissing;
}