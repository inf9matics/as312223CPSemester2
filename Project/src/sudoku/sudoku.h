#ifndef SUDOKU_H
#define SUDOKU_H

#include <functional>
#include <map>
#include <memory>
#include <vector>

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

	std::vector<std::vector<SudokuCell>> cells;

	std::vector<std::vector<SudokuSubMatrix>> subMatrices;

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

	bool checkFilledAtPosition(std::pair<int, int> position);
	bool checkFilled();
	bool getFilled();

	SudokuMatrix *iterateOverCells(std::function<void(SudokuCell *)> function);
	SudokuMatrix *iterateOverSubMatrices(std::function<void(SudokuSubMatrix *)> function);

	std::vector<int> getCrossValuesPresentAtPosition(std::pair<int, int> position);
	std::vector<int> getCrossValuesMissingAtPosition(std::pair<int, int> position);

	std::pair<int, int> findEmptyPosition();

	std::pair<std::pair<int, int>, std::vector<int>> findEmptyPositionWithMissingValues();
};

class SudokuSubMatrix {
      protected:
	SudokuMatrix *parentMatrix;

	int size;
	bool viable;
	bool filled;
	std::pair<int, int> position;

	std::map<int, int> existingValues;

	friend SudokuMatrixMasked;
	std::vector<std::vector<std::pair<int, int>>> cells;

	friend SudokuMatrix;
	SudokuSubMatrix *setParent(SudokuMatrix *parentMatrix);

      public:
	SudokuSubMatrix(int size, std::pair<int, int> position, SudokuMatrix *parentMatrix);

	SudokuMatrix *getParent();

	int getSize();

	bool checkIfViable();

	SudokuSubMatrix *updateExistingValues(std::pair<int, int> position);

	std::vector<int> getValuesMissing();
	std::vector<int> getValuesFilled();
};

class SudokuCell {
      protected:
	SudokuMatrix *parentMatrix;
	std::pair<int, int> position;

	int value;
	bool viable;

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

	SudokuCell *setValue(int value);
	int getValue();
	int getPreviousValue();

	std::pair<int, int> getPosition();

	SudokuCell *addParityCell(SudokuCell *parityCell);

	SudokuCell *copyParityFrom(SudokuCell &sudokuCell);

	SudokuCell *copyParityTo(SudokuCell &sudokuCell);

	template <typename Function> SudokuCell *iterateOverParity(Function function);

	std::vector<int> getMissingValues();
};

#endif