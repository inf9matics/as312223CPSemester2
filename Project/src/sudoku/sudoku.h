#ifndef SUDOKU_H
#define SUDOKU_H

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

	bool checkViableAtPosition(std::pair<int, int> position);
};

class SudokuSubMatrix {
      protected:
	SudokuMatrix *parentMatrix;

	int size;
	bool viable;
	bool filled;
	std::pair<int, int> position;

	friend SudokuMatrixMasked;
	std::vector<std::vector<SudokuCell *>> cells;

	friend SudokuMatrix;
	SudokuSubMatrix *setParent(SudokuMatrix *parentMatrix);

      public:
	SudokuSubMatrix(int size, std::pair<int, int> position, SudokuMatrix *parentMatrix);

	SudokuMatrix *getParent();

	int getSize();

	bool checkIfViable();
};

class SudokuCell {
      protected:
	SudokuMatrix *parentMatrix;
	std::pair<int, int> position;

	int value;
	bool viable;

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

	std::vector<SudokuCell *> parityCells;

	SudokuCell *addParityCell(SudokuCell *parityCell);

	SudokuCell *copyParityFrom(SudokuCell &sudokuCell);
	friend SudokuCell *SudokuCell::copyParityFrom(SudokuCell &SudokuCell);

	SudokuCell *copyParityTo(SudokuCell &sudokuCell);
	friend SudokuCell *SudokuCell::copyParityTo(SudokuCell &sudokuCell);
};

#endif