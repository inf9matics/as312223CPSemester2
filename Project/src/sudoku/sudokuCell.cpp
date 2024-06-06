#include <algorithm>

#include "sudoku.h"

SudokuCell::SudokuCell(std::pair<int, int> position) : position(position), value(0), previousValue(0), viable(true), locked(false) {}

bool SudokuCell::operator==(SudokuCell &sudokuCell) { return ((this->parentMatrix == sudokuCell.parentMatrix) && (this->position == sudokuCell.position)); }

bool SudokuCell::operator!=(SudokuCell &sudokuCell) { return !(*this == sudokuCell); }

SudokuCell &SudokuCell::operator=(const SudokuCell &sudokuCell) {
	this->parentMatrix = sudokuCell.parentMatrix;

	this->parityCells.clear();
	this->parityCells = sudokuCell.parityCells;

	this->value = sudokuCell.value;
	this->previousValue = sudokuCell.previousValue;
	this->position = sudokuCell.position;

	this->viable = this->parentMatrix->checkViableAtPosition(this->position);
	return *this;
}

SudokuCell *SudokuCell::setParent(SudokuMatrix *parentMatrix) {
	this->parentMatrix = parentMatrix;
	return this;
}

SudokuMatrix *SudokuCell::getParent() { return this->parentMatrix; }

std::pair<int, int> SudokuCell::getPosition() { return this->position; }

SudokuCell *SudokuCell::setValue(int value, bool checkParity) {
	if (!this->locked && (value <= this->parentMatrix->getSize())) {
		this->previousValue = this->value;
		this->value = value;

		this->parentMatrix->updateSubMatrixAtCellPosition(this->position);

		if (checkParity && !this->parityCells.empty()) {
			this->calledParity = true;
			this->iterateOverParity([value](SudokuCell *sudokuCell) { sudokuCell->setValue(value); });
			this->calledParity = false;
		}

		this->viable = this->parentMatrix->checkViableAtPosition(this->position);
		this->parentMatrix->checkFilledAtPosition(this->position);
	}

	return this;
}

std::vector<std::pair<int, int>> SudokuCell::getParityCells() { return this->parityCells; }

int SudokuCell::getValue() { return this->value; }

int SudokuCell::getPreviousValue() { return this->previousValue; }

bool SudokuCell::getCalledParity() { return this->calledParity; }

SudokuCell *SudokuCell::addParityCell(SudokuCell *parityCell) {
	this->parityCells.push_back(parityCell->position);

	this->calledParity = true;
	if (!parityCell->getCalledParity()) {
		parityCell->addParityCell(this);
		parityCell->setValue(this->value);
	}
	this->calledParity = false;

	return this;
}

SudokuCell *SudokuCell::copyParityFrom(SudokuCell &sudokuCell) {
	std::vector<std::pair<int, int>>::iterator parityCellsIterator = sudokuCell.parityCells.begin();
	this->parityCells.clear();
	while (parityCellsIterator != sudokuCell.parityCells.end()) {
		this->parityCells.push_back(*parityCellsIterator);
		parityCellsIterator++;
	}

	return this;
}

SudokuCell *SudokuCell::copyParityTo(SudokuCell &sudokuCell) {
	std::vector<std::pair<int, int>>::iterator parityCellsIterator = this->parityCells.begin();
	sudokuCell.parityCells.clear();
	while (parityCellsIterator != sudokuCell.parityCells.end()) {
		sudokuCell.parityCells.push_back(*parityCellsIterator);
		parityCellsIterator++;
	}

	return this;
}

SudokuCell *SudokuCell::iterateOverParity(std::function<void(SudokuCell *)> function) {
	std::vector<std::pair<int, int>>::iterator parityCellsIterator = this->parityCells.begin();
	while (parityCellsIterator != this->parityCells.end()) {
		if (!this->parentMatrix->getCellAtPosition(*parityCellsIterator)->getCalledParity()) {
			function(this->parentMatrix->getCellAtPosition(*parityCellsIterator));
		}
		parityCellsIterator++;
	}

	return this;
}

std::vector<int> SudokuCell::getMissingValues() {
	std::vector<int> subMatrixValuesMissing = this->parentMatrix->getSubMatrixAtCellPosition(this->position)->getValuesMissing();
	std::vector<int> crossValuesMissing = this->parentMatrix->getCrossValuesMissingAtPosition(this->position);

	std::vector<int> valuesMissing;
	std::vector<int>::iterator subMatrixValuesMissingIterator = subMatrixValuesMissing.begin();
	while (subMatrixValuesMissingIterator != subMatrixValuesMissing.end()) {
		if (std::find(crossValuesMissing.begin(), crossValuesMissing.end(), *subMatrixValuesMissingIterator) != crossValuesMissing.end()) {
			valuesMissing.push_back(*subMatrixValuesMissingIterator);
		}
		subMatrixValuesMissingIterator++;
	}

	return valuesMissing;
}

bool SudokuCell::getLocked() { return this->locked; }

bool SudokuCell::getViable() { return this->viable; }

SudokuCell *SudokuCell::lock() {
	this->locked = true;

	return this;
}

SudokuCell *SudokuCell::unlock() {
	this->locked = false;

	return this;
}