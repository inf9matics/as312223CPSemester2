#ifndef BACKSOLVER_H
#define BACKSOLVER_H

#include "sudoku.h"

class SudokuMatrixMasked : public SudokuMatrix {
      protected:
	std::vector<std::vector<SudokuCell>> *cells;

	std::vector<std::vector<SudokuCell *>> cellsMasked;

	SudokuMatrix *parentMatrix;

	bool root;
    
      public:
	SudokuMatrixMasked(SudokuMatrix sudokuMatrix);
	SudokuMatrixMasked(SudokuMatrixMasked &&sudokuMatrixMasked);
	SudokuMatrixMasked(const SudokuMatrixMasked &sudokuMatrixMasked);

	SudokuMatrixMasked &operator=(const SudokuMatrixMasked &sudokuMatrixMasked);

	operator SudokuMatrix();

	SudokuCell &getCellAtPosition(std::pair<int, int> position);
};

class SudokuBacksolver {};

#endif