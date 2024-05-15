#include "backsolver.h"

SudokuMatrixMasked::SudokuMatrixMasked(SudokuMatrix &sudokuMatrix) : SudokuMatrix(sudokuMatrix), cells{sudokuMatrix.cells} {
	this->parentMatrix = &sudokuMatrix;

	this->root = true;

	for (int i{0}; i < this->size; i++) {
		std::vector<SudokuCell *> row;
		for (int j{0}; j < this->size; j++) {
			row.push_back(&this->cells.at(i).at(j));
		}
		this->cellsMasked.push_back(row);
	}

	this->subMatrices.clear();
	this->prepareSubMatrices();
}

SudokuMatrixMasked::SudokuMatrixMasked(const SudokuMatrixMasked &sudokuMatrixMasked) : SudokuMatrix(*sudokuMatrixMasked.parentMatrix), cells{sudokuMatrixMasked.cells} {
	this->cellsMasked = sudokuMatrixMasked.cellsMasked;

	this->root = false;

	this->subMatrices.clear();
	this->subMatrices = sudokuMatrixMasked.subMatrices;

	this->parentMatrix = sudokuMatrixMasked.parentMatrix;
}

SudokuMatrixMasked::~SudokuMatrixMasked() {
	std::vector<SudokuCell *>::iterator cellsManagedIterator = this->cellsManaged.begin();
	while (cellsManagedIterator != this->cellsManaged.end()) {
		delete *cellsManagedIterator;
		cellsManagedIterator++;
	}
}

SudokuCell *SudokuMatrixMasked::setValueAt(std::pair<int, int> position, int value) {
	SudokuCell *cell;
	cell = this->getCellAtPosition(position);

	if (value > this->size) {
		return cell;
	}

	if (cell->getValue() == 0) {
		cell = new SudokuCell{position};
		this->cellsManaged.emplace_back(cell);
		this->cellsManaged.back()->setParent(this);
		this->getSubMatrixAtCellPosition(position)->cells.at(position.first % this->subMatrixSize).at(position.second % this->subMatrixSize) = this->cellsManaged.back();
		this->cellsMasked.at(position.first).at(position.second) = this->cellsManaged.back();
	}

	return cell->setValue(value);
}

SudokuCell *SudokuMatrixMasked::getCellAtPosition(std::pair<int, int> position) {
	SudokuCell *cell;
	cell = this->cellsMasked.at(position.first).at(position.second);
	if (cell->getValue() == 0) {
		if (this->root) {
			cell = &cells.at(position.first).at(position.second);
		} else {
			cell = this->parentMatrix->getCellAtPosition(position);
		}
	}

	return cell;
}