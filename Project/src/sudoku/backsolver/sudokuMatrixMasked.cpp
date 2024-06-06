#include "backsolver.h"

SudokuMatrixMasked::SudokuMatrixMasked(SudokuMatrix &sudokuMatrix) : SudokuMatrix(sudokuMatrix) {
	this->parentMatrix = &sudokuMatrix;

	this->cells = &sudokuMatrix.cells;

	for (int i{0}; i < this->size; i++) {
		for (int j{0}; j < this->size; j++) {
			SudokuCell *sudokuCell = new SudokuCell{this->cells->at({i, j})};
			sudokuCell->setParent(this);

			this->cellsMasked.insert({{i, j}, sudokuCell});
		}
	}

	this->subMatrices.clear();
	this->prepareSubMatrices();

	this->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });
}

SudokuMatrixMasked::SudokuMatrixMasked(SudokuMatrixMasked &&sudokuMatrixMasked) {
	(*this) = sudokuMatrixMasked;

	sudokuMatrixMasked.subMatrices.clear();

	sudokuMatrixMasked.size = -1;

	sudokuMatrixMasked.viable = NULL;
	sudokuMatrixMasked.filled = NULL;

	sudokuMatrixMasked.filledAmount = -1;

	this->cellsManaged = sudokuMatrixMasked.cellsManaged;
	sudokuMatrixMasked.cellsManaged.clear();
}

SudokuMatrixMasked::SudokuMatrixMasked(const SudokuMatrixMasked &sudokuMatrixMasked) : SudokuMatrix(*sudokuMatrixMasked.parentMatrix), cells{sudokuMatrixMasked.cells} { *this = sudokuMatrixMasked; }

SudokuMatrixMasked &SudokuMatrixMasked::operator=(const SudokuMatrixMasked &sudokuMatrixMasked) {
	(*this) = sudokuMatrixMasked;

	this->cells = sudokuMatrixMasked.cells;
	this->cellsMasked = sudokuMatrixMasked.cellsMasked;
	this->iterateOverCellsMasked([this](SudokuCell *sudokuCell) { sudokuCell->setParent(this); });

	this->subMatrices.clear();
	this->subMatrices = sudokuMatrixMasked.subMatrices;
	this->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });

	this->parentMatrix = sudokuMatrixMasked.parentMatrix;

	return *this;
}

SudokuMatrixMasked::~SudokuMatrixMasked() {
	std::set<std::pair<int, int>>::iterator cellsManagedIterator = this->cellsManaged.begin();
	while (cellsManagedIterator != this->cellsManaged.end()) {
		delete this->cellsMasked.at(*cellsManagedIterator);
		cellsManagedIterator++;
	}
}

SudokuCell *SudokuMatrixMasked::setValueAt(std::pair<int, int> position, int value) {
	SudokuCell *cell;
	cell = this->cellsMasked.at(position);

	if (value > this->size) {
		return cell;
	}

	if (this->cellsManaged.count(position) == 0) {
		SudokuCell *cellManaged = new SudokuCell(*cell);
		cellManaged->setParent(this);
		this->cellsManaged.insert(position);
		this->cellsMasked.at(position) = cellManaged;
		cell = cellManaged;
		std::vector<SudokuCell *> newParityCells;
		std::vector<std::pair<int, int>>::iterator parityCellsIterator = cellManaged->parityCells.begin();
		while (parityCellsIterator != cellManaged->parityCells.end()) {
			newParityCells.emplace_back(this->getCellAtPosition(*parityCellsIterator));
			this->cellsMasked.at(*parityCellsIterator) = newParityCells.back();
			this->cellsManaged.insert(*parityCellsIterator);
			parityCellsIterator++;
		}
	}

	return cell->setValue(value);
}

SudokuCell *SudokuMatrixMasked::getCellAtPosition(std::pair<int, int> position) { return this->cellsMasked.at(position); }

SudokuMatrixMasked *SudokuMatrixMasked::iterateOverCellsMasked(std::function<void(SudokuCell *)> function) {
	std::map<std::pair<int, int>, SudokuCell *>::iterator cellsMaskedIterator = this->cellsMasked.begin();
	while (cellsMaskedIterator != this->cellsMasked.end()) {
		function(cellsMaskedIterator->second);
		cellsMaskedIterator++;
	}

	return this;
}

SudokuMatrix SudokuMatrixMasked::getSudokuMatrix() {
	SudokuMatrix sudokuMatrix{this->subMatrixSize};

	this->iterateOverCellsMasked([this, &sudokuMatrix](SudokuCell *sudokuCell) { sudokuMatrix.getCellAtPosition(sudokuCell->position)->setValue(this->getCellAtPosition(sudokuCell->position)->getValue()); });

	return sudokuMatrix;
}