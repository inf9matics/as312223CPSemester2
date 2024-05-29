#include "backsolver.h"

SudokuMatrixMasked::SudokuMatrixMasked(SudokuMatrix &sudokuMatrix) : SudokuMatrix(sudokuMatrix) {
	this->parentMatrix = &sudokuMatrix;

	this->cells = new std::vector<std::vector<SudokuCell>>{};
	*this->cells = sudokuMatrix.cells;

	std::vector<std::vector<SudokuCell>>::iterator rowsIterator = this->cells->begin();
	while (rowsIterator != this->cells->end()) {
		std::vector<SudokuCell>::iterator columnsIterator = rowsIterator->begin();
		while (columnsIterator != rowsIterator->end()) {
			columnsIterator->setParent(this);
			columnsIterator++;
		}
		rowsIterator++;
	}

	// this->root = true;

	for (int i{0}; i < this->size; i++) {
		std::vector<SudokuCell *> row;
		for (int j{0}; j < this->size; j++) {
			row.push_back(&this->cells->at(i).at(j));
			row.back()->setParent(this);
		}
		this->cellsMasked.push_back(row);
	}

	this->subMatrices.clear();
	this->prepareSubMatrices();
}

SudokuMatrixMasked::SudokuMatrixMasked(SudokuMatrixMasked &&sudokuMatrixMasked) {
	*this = sudokuMatrixMasked;

	sudokuMatrixMasked.cells = nullptr;

	std::vector<std::vector<SudokuSubMatrix>>::iterator subMatricesIterator = sudokuMatrixMasked.subMatrices.begin();
	while (subMatricesIterator != sudokuMatrixMasked.subMatrices.end()) {
		subMatricesIterator->clear();
		subMatricesIterator++;
	}
	sudokuMatrixMasked.subMatrices.clear();

	sudokuMatrixMasked.size = -1;

	this->cellsManaged = sudokuMatrixMasked.cellsManaged;
	sudokuMatrixMasked.cellsManaged.clear();
}

SudokuMatrixMasked::SudokuMatrixMasked(const SudokuMatrixMasked &sudokuMatrixMasked) : SudokuMatrix(*sudokuMatrixMasked.parentMatrix), cells{sudokuMatrixMasked.cells} { *this = sudokuMatrixMasked; }

SudokuMatrixMasked &SudokuMatrixMasked::operator=(const SudokuMatrixMasked &sudokuMatrixMasked) {
	this->cells = sudokuMatrixMasked.cells;
	this->cellsMasked = sudokuMatrixMasked.cellsMasked;
	this->iterateOverCellsMasked([this](SudokuCell *sudokuCell) { sudokuCell->setParent(this); });

	this->subMatrices.clear();
	this->subMatrices = sudokuMatrixMasked.subMatrices;

	this->parentMatrix = sudokuMatrixMasked.parentMatrix;

	return *this;
}

SudokuMatrixMasked::~SudokuMatrixMasked() {
	std::set<std::pair<int, int>>::iterator cellsManagedIterator = this->cellsManaged.begin();
	while (cellsManagedIterator != this->cellsManaged.end()) {
		delete this->cellsMasked.at(cellsManagedIterator->first).at(cellsManagedIterator->second);
		cellsManagedIterator++;
	}
}

SudokuCell *SudokuMatrixMasked::setValueAt(std::pair<int, int> position, int value) {
	SudokuCell *cell;
	cell = this->cellsMasked.at(position.first).at(position.second);

	if (value > this->size) {
		return cell;
	}

	if (this->cellsManaged.count(position) == 0) {
		SudokuCell *cellManaged = new SudokuCell(*cell);
		cellManaged->setParent(this);
		this->cellsManaged.insert(position);
		this->cellsMasked.at(position.first).at(position.second) = cellManaged;
		cell = cellManaged;
		std::vector<SudokuCell *> newParityCells;
		std::vector<std::pair<int, int>>::iterator parityCellsIterator = cellManaged->parityCells.begin();
		while (parityCellsIterator != cellManaged->parityCells.end()) {
			newParityCells.emplace_back(this->getCellAtPosition(*parityCellsIterator));
			this->cellsMasked.at(parityCellsIterator->first).at(parityCellsIterator->second) = newParityCells.back();
			this->cellsManaged.insert(*parityCellsIterator);
			parityCellsIterator++;
		}
	}

	return cell->setValue(value);
}

SudokuCell *SudokuMatrixMasked::getCellAtPosition(std::pair<int, int> position) { return this->cellsMasked.at(position.first).at(position.second); }

template <typename Function> SudokuMatrixMasked *SudokuMatrixMasked::iterateOverCellsMasked(Function function) {
	std::vector<std::vector<SudokuCell *>>::iterator rowIterator = this->cellsMasked.begin();
	while (rowIterator != this->cellsMasked.end()) {
		std::vector<SudokuCell *>::iterator columnIterator = rowIterator->begin();
		while (columnIterator != rowIterator->end()) {
			function(*columnIterator);
			columnIterator++;
		}
		rowIterator++;
	}

	return this;
}