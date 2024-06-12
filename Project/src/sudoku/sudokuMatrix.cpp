#include <cmath>

#include "sudoku.h"

SudokuMatrix::SudokuMatrix() : size(9), subMatrixSize(3), viable(false), filled(false), filledAmount(0) {
	this->prepareCells()->prepareSubMatrices();

	this->iterateOverCells([](SudokuCell *sudokuCell) { sudokuCell->viable = sudokuCell->getParent()->checkViableAtPosition(sudokuCell->getPosition()); });
	this->iterateOverSubMatrices([](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->checkIfViable(); });
}

SudokuMatrix::SudokuMatrix(int subMatrixSize) : size(std::pow(subMatrixSize, 2)), subMatrixSize(subMatrixSize), viable(false), filled(false), filledAmount(0) {
	this->prepareCells()->prepareSubMatrices();

	this->iterateOverCells([](SudokuCell *sudokuCell) { sudokuCell->viable = sudokuCell->getParent()->checkViableAtPosition(sudokuCell->getPosition()); });
	this->iterateOverSubMatrices([](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->checkIfViable(); });
}

SudokuMatrix::SudokuMatrix(const SudokuMatrix &sudokuMatrix)
    : size(sudokuMatrix.size), subMatrixSize(sudokuMatrix.subMatrixSize), viable(sudokuMatrix.viable), filled(sudokuMatrix.filled), filledAmount(sudokuMatrix.filledAmount), cells(sudokuMatrix.cells), subMatrices(sudokuMatrix.subMatrices) {
	this->iterateOverCells([this](SudokuCell *sudokuCell) { sudokuCell->setParent(this); });
	this->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });
}

SudokuMatrix::SudokuMatrix(SudokuMatrix &&sudokuMatrix)
    : size(sudokuMatrix.size), subMatrixSize(sudokuMatrix.subMatrixSize), viable(sudokuMatrix.viable), filled(sudokuMatrix.filled), filledAmount(sudokuMatrix.filledAmount), cells(sudokuMatrix.cells), subMatrices(sudokuMatrix.subMatrices) {
	sudokuMatrix.size = -1;

	sudokuMatrix.subMatrixSize = -1;

	sudokuMatrix.viable = NULL;
	sudokuMatrix.filled = NULL;

	sudokuMatrix.filledAmount = -1;

	sudokuMatrix.cells.clear();
	this->iterateOverCells([this](SudokuCell *sudokuCell) { sudokuCell->setParent(this); });

	sudokuMatrix.subMatrices.clear();
	this->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });

	sudokuMatrix.~SudokuMatrix();
}

SudokuMatrix &SudokuMatrix::operator=(const SudokuMatrix &sudokuMatrix) {
	this->size = sudokuMatrix.size;
	this->subMatrixSize = sudokuMatrix.subMatrixSize;

	this->viable = sudokuMatrix.viable;
	this->filled = sudokuMatrix.filled;

	this->filledAmount = sudokuMatrix.filledAmount;

	this->cells.clear();
	this->cells = sudokuMatrix.cells;
	this->iterateOverCells([this](SudokuCell *sudokuCell) { sudokuCell->setParent(this); });

	this->subMatrices.clear();
	this->subMatrices = sudokuMatrix.subMatrices;
	this->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });

	return *this;
}

SudokuMatrix *SudokuMatrix::prepareCells() {
	for (int i{0}; i < this->size; i++) {
		for (int j{0}; j < this->size; j++) {
			this->cells.insert({{i, j}, {{i, j}}});
			this->cells.at({i, j}).setParent(this);
		}
	}
	return this;
}

SudokuMatrix *SudokuMatrix::prepareSubMatrices() {
	for (int i{0}; i < this->subMatrixSize; i++) {
		for (int j{0}; j < this->subMatrixSize; j++) {
			this->subMatrices.insert({{i, j}, {this->subMatrixSize, {i, j}, this}});
			this->subMatrices.at({i, j}).setParent(this);
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

SudokuCell *SudokuMatrix::getCellAtPosition(std::pair<int, int> position) { return &this->cells.at(position); }

SudokuSubMatrix *SudokuMatrix::getSubMatrixAtPosition(std::pair<int, int> position) { return &this->subMatrices.at(position); }

std::pair<int, int> SudokuMatrix::cellPositionInSubMatrix(std::pair<int, int> cellPosition) {
	std::pair<int, int> position;
	position.first = cellPosition.first % this->subMatrixSize;
	position.second = cellPosition.second % this->subMatrixSize;

	return position;
}

SudokuSubMatrix *SudokuMatrix::getSubMatrixAtCellPosition(std::pair<int, int> position) {
	std::pair<int, int> subMatrixPosition{std::floor((position.first / this->subMatrixSize)), std::floor((position.second / this->subMatrixSize))};

	return this->getSubMatrixAtPosition(subMatrixPosition);
}

bool SudokuMatrix::checkViableAtPosition(std::pair<int, int> position) {
	bool viable{true};
	SudokuCell *currentCell = this->getCellAtPosition(position);

	if (currentCell->getValue() != 0) {
		for (int i{0}; viable && (i < this->size); i++) {
			if ((i != position.second) && (currentCell->getValue() == this->getCellAtPosition({position.first, i})->getValue())) {
				viable = false;
			}
			if ((i != position.first) && (currentCell->getValue() == this->getCellAtPosition({i, position.second})->getValue())) {
				viable = false;
			}
		}
	}

	bool subMatrixViable{false};
	if (this->getSubMatrixAtCellPosition(position)->getExistingValues().at(currentCell->getValue()) < 2) {
		subMatrixViable = true;
	}

	viable = viable && subMatrixViable;

	this->viable = viable;

	return this->viable;
}

SudokuMatrix *SudokuMatrix::updateSubMatrixAtCellPosition(std::pair<int, int> position) {
	this->getSubMatrixAtCellPosition(position)->updateExistingValues(this->cellPositionInSubMatrix(position))->checkIfViable();

	return this;
}

SudokuMatrix *SudokuMatrix::iterateOverCells(std::function<void(SudokuCell *)> function) {
	std::map<std::pair<int, int>, SudokuCell>::iterator cellsIterator = this->cells.begin();
	while (cellsIterator != this->cells.end()) {
		function(&cellsIterator->second);
		cellsIterator++;
	}

	return this;
}

SudokuMatrix *SudokuMatrix::iterateOverSubMatrices(std::function<void(SudokuSubMatrix *)> function) {
	std::map<std::pair<int, int>, SudokuSubMatrix>::iterator subMatricesIterator = this->subMatrices.begin();
	while (subMatricesIterator != this->subMatrices.end()) {
		function(&subMatricesIterator->second);
		subMatricesIterator++;
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
		if (filled && sudokuCell->getValue() == 0) {
			filled = false;
		}
	});

	this->filled = filled;
	return this->filled;
}

SudokuMatrix *SudokuMatrix::removeNoisyNumberOfCells(int numberOfCells) {
	int variance{this->subMatrixSize};

	int removeNumber = numberOfCells;
	removeNumber += (std::rand() % (variance * 2)) - variance;
	for (int i{0}; i < removeNumber; i++) {
		int randX = std::rand() % this->size;
		int randY = std::rand() % this->size;

		if (this->getCellAtPosition({randX, randY})->getValue() == 0) {
			i--;
		} else {
			this->getCellAtPosition({randX, randY})->setValue(0);
		}
	}

	return this;
}

bool SudokuMatrix::checkFilledAtPosition(std::pair<int, int> position) {
	SudokuCell *cell = this->getCellAtPosition(position);
	if (cell->previousValue > 0) {
		if (cell->value == 0) {
			this->filledAmount--;
		}
	} else {
		if (cell->value > 0) {
			this->filledAmount++;
		}
	}

	if (this->filledAmount == std::pow(this->size, 2)) {
		this->filled = true;
	} else {
		this->filled = false;
	}

	return this->filled;
}

SudokuMatrix *SudokuMatrix::lockFilled() {
	this->iterateOverCells([](SudokuCell *sudokuCell) {
		if (sudokuCell->getValue() > 0) {
			sudokuCell->lock();
		}
	});

	return this;
}

bool SudokuMatrix::getFilled() { return this->filled; }

std::vector<int> SudokuMatrix::getCrossValuesPresentAtPosition(std::pair<int, int> position) {
	std::vector<int> valuesPresent;
	for (int i{0}; i <= this->getSize(); i++) {
		valuesPresent.push_back(0);
	}

	for (int i{0}; i < this->size; i++) {
		if (position.first != i) {
			valuesPresent.at(this->getCellAtPosition({i, position.second})->getValue())++;
		}
		if (position.second != i) {
			valuesPresent.at(this->getCellAtPosition({position.first, i})->getValue())++;
		}
	}

	return valuesPresent;
}

std::vector<int> SudokuMatrix::getCrossValuesMissingAtPosition(std::pair<int, int> position) {
	std::vector<int> valuesPresent = this->getCrossValuesPresentAtPosition(position);

	std::vector<int> valuesMissing;
	std::vector<int>::iterator valuesPresentIterator = valuesPresent.begin();
	valuesPresentIterator++;
	while (valuesPresentIterator != valuesPresent.end()) {
		if (*valuesPresentIterator == 0) {
			valuesMissing.push_back(std::distance(valuesPresent.begin(), valuesPresentIterator));
		}
		valuesPresentIterator++;
	}

	return valuesMissing;
}

std::pair<int, int> SudokuMatrix::findEmptyPosition() {
	std::pair<int, int> position{-1, -1};

	for (int i{0}; i < this->getSize(); i++) {
		for (int j{0}; j < this->getSize(); j++) {
			if (this->getCellAtPosition({i, j})->getValue() == 0) {
				position = {i, j};

				return position;
			}
		}
	}

	return position;
}

std::pair<std::pair<int, int>, std::vector<int>> SudokuMatrix::findEmptyPositionWithMissingValues() {
	std::pair<int, int> emptyPosition{-1, -1};
	std::vector<int> missingValues;

	for (int i{0}; i < this->getSize(); i++) {
		for (int j{0}; j < this->getSize(); j++) {
			if (this->getCellAtPosition({i, j})->getValue() == 0) {
				missingValues = this->getCellAtPosition({i, j})->getMissingValues();
				if (!missingValues.empty()) {
					emptyPosition = {i, j};
					i = this->getSize();
					j = this->getSize();
				}
			}
		}
	}

	return std::pair<std::pair<int, int>, std::vector<int>>{emptyPosition, missingValues};
}

SudokuMatrix *SudokuMatrix::updateViableFromCellPosition(std::pair<int, int> cellPosition) {
	SudokuCell *currentCell = this->getCellAtPosition(cellPosition);
	for (int i{0}; i < this->size; i++) {
		if (i != cellPosition.first) {
			SudokuCell *workingCell = this->getCellAtPosition({i, currentCell->getPosition().second});
			if (!workingCell->getViable()) {
				workingCell->setViable(workingCell->parentMatrix->checkViableAtPosition(workingCell->getPosition()));
			}
		}
		if (i != cellPosition.second) {
			SudokuCell *workingCell = this->getCellAtPosition({currentCell->getPosition().first, i});
			if (!workingCell->getViable()) {
				workingCell->setViable(workingCell->parentMatrix->checkViableAtPosition(workingCell->getPosition()));
			}
		}
	}

	SudokuSubMatrix *currentSubMatrix = this->getSubMatrixAtCellPosition(cellPosition);
	currentSubMatrix->iterateOverCells([](SudokuCell *sudokuCell) {
		if (!sudokuCell->getViable()) {
			sudokuCell->setViable(sudokuCell->getParent()->checkViableAtPosition(sudokuCell->getPosition()));
		}
	});

	return this;
}