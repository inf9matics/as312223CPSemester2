#ifndef BACKSOLVER_H
#define BACKSOLVER_H

#include "sudoku.h"

class SudokuMatrixMasked : public SudokuMatrix {
      protected:
	std::vector<std::vector<SudokuCell>> *cells;

	std::vector<std::vector<SudokuCell *>> cellsMasked;

	std::vector<SudokuCell *> cellsManaged;

	SudokuMatrix *parentMatrix;

	bool root;

	SudokuMatrixMasked *prepareCellsMasked();
    
      public:
	SudokuMatrixMasked(SudokuMatrix sudokuMatrix);
	SudokuMatrixMasked(SudokuMatrixMasked &&sudokuMatrixMasked);
	SudokuMatrixMasked(const SudokuMatrixMasked &sudokuMatrixMasked);

	~SudokuMatrixMasked();

	SudokuMatrixMasked &operator=(const SudokuMatrixMasked &sudokuMatrixMasked);

	operator SudokuMatrix();

	SudokuCell *setValueAt(std::pair<int, int> position, int value);

	SudokuCell *getCellAtPosition(std::pair<int, int> position);
};

class SudokuBacksolver {};

#endif