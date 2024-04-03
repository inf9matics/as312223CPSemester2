#ifndef SUDOKU_H
#define SUDOKU_H

#include <memory>
#include <vector>

class SudokuCell;

class SudokuSubMatrix;

class SudokuMatrix {
	friend class SudokuCell;

      protected:
	int size;

	std::vector<std::vector<SudokuCell>> cells;

    std::vector<std::vector<SudokuSubMatrix>> subMatrices;

	std::pair<bool, std::vector<SudokuMatrix> *> solve(std::vector<SudokuMatrix> &subMatrices);

      public:
	SudokuMatrix(int size);

    SudokuCell& setValueAt(std::pair<int, int> position, int value);

    SudokuCell& getAtPosition(std::pair<int, int> position);
};

class SudokuSubMatrix {
    protected:
    int size;

    std::vector<std::vector<std::shared_ptr<SudokuCell>>> cells;

    public:
    SudokuSubMatrix(int size);
};

class SudokuCell {
    friend class SudokuSubMatrix;

	std::pair<int, int> position;

	int value;
	bool viable;

	bool checkIfViable(SudokuMatrix& matrix);

      public:
	SudokuCell(std::pair<int, int> position, SudokuMatrix& matrix);

    SudokuCell& setValue(int value, SudokuMatrix &matrix);
};

#endif