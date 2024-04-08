#ifndef SUDOKU_H
#define SUDOKU_H

#include <memory>
#include <vector>

class SudokuCell;

class SudokuSubMatrix;

class SudokuMatrix {
      protected:
	int size;
	int subMatrixSize;

	std::vector<std::vector<SudokuCell>> cells;

	std::vector<std::vector<SudokuSubMatrix>> subMatrices;

	std::pair<bool, std::vector<SudokuMatrix> *> solve(std::vector<SudokuMatrix> &subMatrices);

      public:
	SudokuMatrix(int size);

	SudokuCell &setValueAt(std::pair<int, int> position, int value);

	SudokuCell &getCellAtPosition(std::pair<int, int> position);

	SudokuSubMatrix &getSubMatrixAtPosition(std::pair<int, int> position);

	SudokuSubMatrix &getSubMatrixAtCellPosition(std::pair<int, int> position);

	bool checkViableAtPosition(std::pair<int, int> position);
};

class SudokuSubMatrix {
      protected:
	SudokuMatrix *parentMatrix;

	int size;
	bool viable;
	bool filled;
	std::pair<int, int> position;

	std::vector<std::vector<SudokuCell *>> cells;

	friend class SudokuMatrix;
	SudokuSubMatrix &setCellAt(std::pair<int, int> position);

      public:
	SudokuSubMatrix(int size, std::pair<int, int> position, SudokuMatrix &parentMatrix);

	bool checkIfViable();
};

class SudokuCell {
      protected:
	SudokuMatrix *parentMatrix;
	SudokuSubMatrix *parentSubMatrix;

	SudokuCell *parityCell;

	std::pair<int, int> position;

	int value;
	bool viable;

	bool calledParity;

      public:
	SudokuCell(std::pair<int, int> position, SudokuMatrix &parentMatrix);

	SudokuCell &setValue(int value);

	SudokuCell &setParityCell(SudokuCell &parityCell);

	int getValue();

	bool getCalledParity();
};

#endif