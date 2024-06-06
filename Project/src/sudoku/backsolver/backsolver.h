#ifndef BACKSOLVER_H
#define BACKSOLVER_H

#include <set>

#include "sudoku.h"

class SudokuMatrixMasked : public SudokuMatrix {
      protected:
	std::map<std::pair<int, int>, SudokuCell> *cells;

	std::map<std::pair<int, int>, SudokuCell *> cellsMasked;

	std::set<std::pair<int, int>> cellsManaged;

	SudokuMatrix *parentMatrix;

	// bool root;

	SudokuMatrixMasked *prepareCellsMasked();

      public:
	SudokuMatrixMasked(SudokuMatrix &sudokuMatrix);
	SudokuMatrixMasked(SudokuMatrixMasked &&sudokuMatrixMasked);
	SudokuMatrixMasked(const SudokuMatrixMasked &sudokuMatrixMasked);

	~SudokuMatrixMasked();

	SudokuMatrixMasked &operator=(const SudokuMatrixMasked &sudokuMatrixMasked);

	SudokuCell *setValueAt(std::pair<int, int> position, int value);

	SudokuCell *getCellAtPosition(std::pair<int, int> position);

	SudokuMatrixMasked *iterateOverCellsMasked(std::function<void(SudokuCell *)> function);
	SudokuMatrix getSudokuMatrix();
};

class SudokuBacksolver {
      protected:
	SudokuMatrix sudokuMatrix;

	std::pair<bool, SudokuMatrix *> recurseSolveMatrix(SudokuMatrixMasked &sudokuMaskedMatrix);

      public:
	SudokuBacksolver(SudokuMatrix &sudokuMatrix);

	std::pair<bool, SudokuMatrix> solveMatrix();
};

#endif