#ifndef SUDOKU_H
#define SUDOKU_H

#include <memory>
#include <vector>
#include <map>

class SudokuMatrixMasked;

class SudokuCell;

class SudokuSubMatrix;

class SudokuMatrix {
	friend class SudokuMatrixMasked;

      protected:
	int size;
	int subMatrixSize;

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

	SudokuCell *getCellAtPosition(std::pair<int, int> position);

	SudokuSubMatrix *getSubMatrixAtPosition(std::pair<int, int> position);
	SudokuSubMatrix *getSubMatrixAtCellPosition(std::pair<int, int> position);

	SudokuMatrix *updateSubMatrixAtCellPosition(std::pair<int, int> position);

	bool checkViableAtPosition(std::pair<int, int> position);
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
	SudokuCell *setParent(SudokuMatrix *parentMatrix);

      public:
	SudokuCell(std::pair<int, int> position);

	bool operator==(SudokuCell &sudokuCell);
	bool operator!=(SudokuCell &sudokuCell);

	SudokuCell &operator=(const SudokuCell &sudokuCell);

	SudokuMatrix *getParent();

	SudokuCell *setValue(int value);
	int getValue();
	int getPreviousValue();

	SudokuCell *addParityCell(SudokuCell *parityCell);

	SudokuCell *copyParityFrom(SudokuCell &sudokuCell);

	SudokuCell *copyParityTo(SudokuCell &sudokuCell);

	template<typename Function>
	SudokuCell *iterateOverParity(Function f);
};

#endif