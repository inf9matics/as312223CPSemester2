#include "sudoku.h"

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
	this->previousValue = this->value;
	this->value = value;
	this->viable = this->parentMatrix->updateSubMatrixAtCellPosition(this->position)->checkViableAtPosition(this->position);

	if (!this->parityCells.empty()) {
		this->calledParity = true;
		this->iterateOverParity([value](SudokuCell *sudokuCell) { sudokuCell->setValue(value); });
		this->calledParity = false;
	}

	return this;
}

int SudokuCell::getValue() { return this->value; }

int SudokuCell::getPreviousValue() { return this->previousValue; }

bool SudokuCell::getCalledParity() { return this->calledParity; }

SudokuCell *SudokuCell::addParityCell(SudokuCell *parityCell) {
	this->parityCells.push_back(parityCell->position);

	this->calledParity = true;
	if (!parityCell->getCalledParity()) {
		parityCell->addParityCell(this);
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

template <typename Function> SudokuCell *SudokuCell::iterateOverParity(Function function) {
	std::vector<std::pair<int, int>>::iterator parityCellsIterator = this->parityCells.begin();
	while (parityCellsIterator != this->parityCells.end()) {
		if (!this->parentMatrix->getCellAtPosition(*parityCellsIterator)->getCalledParity()) {
			function(this->parentMatrix->getCellAtPosition(*parityCellsIterator));
		}
		parityCellsIterator++;
	}

	return this;
}