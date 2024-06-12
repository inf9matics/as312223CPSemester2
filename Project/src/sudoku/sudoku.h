#ifndef SUDOKU_H
#define SUDOKU_H

#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <random>

class SudokuMatrixMasked;

class SudokuCell;

class SudokuSubMatrix;

class SudokuMatrix {
	friend class SudokuMatrixMasked;

      protected:
	int size;
	int subMatrixSize;

	bool viable;

	bool filled;
	int filledAmount;

	std::map<std::pair<int, int>, SudokuCell> cells;

	std::map<std::pair<int, int>, SudokuSubMatrix> subMatrices;

	SudokuMatrix *prepareCells();

	SudokuMatrix *prepareSubMatrices();

      public:
	SudokuMatrix();
	SudokuMatrix(int subMatrixSize);
	SudokuMatrix(SudokuMatrix &&sudokuMatrix);
	SudokuMatrix(const SudokuMatrix &sudokuMatrix);

	SudokuMatrix &operator=(const SudokuMatrix &sudokuMatrix);

	int getSize();
	int getSubMatrixSize();

	SudokuCell *setValueAt(std::pair<int, int> position, int value);

	virtual SudokuCell *getCellAtPosition(std::pair<int, int> position);

	SudokuSubMatrix *getSubMatrixAtPosition(std::pair<int, int> position);
	SudokuSubMatrix *getSubMatrixAtCellPosition(std::pair<int, int> position);

	SudokuMatrix *updateSubMatrixAtCellPosition(std::pair<int, int> position);

	bool checkViableAtPosition(std::pair<int, int> position);
	bool checkViable();
	bool getViable();

	SudokuMatrix *lockFilled();

	bool checkFilledAtPosition(std::pair<int, int> position);
	virtual bool checkFilled();
	bool getFilled();

	SudokuMatrix *removeNoisyNumberOfCells(int numberOfCells);

	SudokuMatrix *iterateOverCells(std::function<void(SudokuCell *)> function);
	SudokuMatrix *iterateOverSubMatrices(std::function<void(SudokuSubMatrix *)> function);

	std::vector<int> getCrossValuesPresentAtPosition(std::pair<int, int> position);
	std::vector<int> getCrossValuesMissingAtPosition(std::pair<int, int> position);

	std::pair<int, int> findEmptyPosition();

	std::pair<std::pair<int, int>, std::vector<int>> findEmptyPositionWithMissingValues();

	std::pair<int, int> cellPositionInSubMatrix(std::pair<int, int> cellPosition);

	SudokuMatrix *updateViableFromCellPosition(std::pair<int, int> cellPosition);
};

class SudokuSubMatrix {
      protected:
	SudokuMatrix *parentMatrix;

	int size;
	bool viable;
	bool filled;
	std::pair<int, int> position;

	std::map<int, int> existingValues;

	std::map<std::pair<int, int>, std::pair<int, int>> cells;

	friend SudokuMatrix;
	friend SudokuMatrixMasked;

      public:
	SudokuSubMatrix(int size, std::pair<int, int> position, SudokuMatrix *parentMatrix);
	SudokuSubMatrix(const SudokuSubMatrix &sudokuSubMatrix);

	SudokuSubMatrix &operator=(const SudokuSubMatrix &sudokuSubMatrix);

	SudokuSubMatrix *setParent(SudokuMatrix *parentMatrix);
	SudokuMatrix *getParent();

	int getSize();

	bool checkIfViable();
	bool getViable();

	SudokuSubMatrix *updateExistingValues(std::pair<int, int> position);

	std::vector<int> getValuesMissing();
	std::vector<int> getValuesFilled();

	std::map<int, int> getExistingValues();

	SudokuSubMatrix *iterateOverCells(std::function<void(SudokuCell *)> function);
};

class SudokuCell {
      protected:
	SudokuMatrix *parentMatrix;
	std::pair<int, int> position;

	int value;
	bool viable;

	bool locked;

	int previousValue;

	std::vector<std::pair<int, int>> parityCells;
	bool calledParity;

	bool getCalledParity();

	friend SudokuMatrix;
	friend SudokuMatrixMasked;

      public:
	SudokuCell(std::pair<int, int> position);

	bool operator==(SudokuCell &sudokuCell);
	bool operator!=(SudokuCell &sudokuCell);

	SudokuCell &operator=(const SudokuCell &sudokuCell);

	SudokuCell *setParent(SudokuMatrix *parentMatrix);
	SudokuMatrix *getParent();

	virtual SudokuCell *setValue(int value, bool checkParity = true);
	int getValue();
	int getPreviousValue();

	virtual SudokuCell *setViable(bool viable);

	bool getViable();

	std::pair<int, int> getPosition();

	SudokuCell *addParityCell(std::pair<int, int> parityCellPosition);

	SudokuCell *copyParityFrom(SudokuCell &sudokuCell);

	SudokuCell *copyParityTo(SudokuCell &sudokuCell);

	SudokuCell *iterateOverParity(std::function<void(SudokuCell *)> function);

	std::vector<int> getMissingValues();

	std::vector<std::pair<int, int>> getParityCells();

	bool getLocked();

	SudokuCell *lock();
	SudokuCell *unlock();
};

#endif