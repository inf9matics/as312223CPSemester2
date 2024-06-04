#ifndef SUDOKU_QT_H
#define SUDOKU_QT_H

#include <QGridLayout>
#include <QLabel>

#include <functional>

#include "sudoku.h"

class SudokuCellQt;

class SudokuMatrixQt : public QGridLayout, public SudokuMatrix {
	Q_OBJECT

      protected:
	std::vector<std::vector<SudokuCellQt *>> cellsQt;

      public:
	SudokuMatrixQt(QWidget *parent = nullptr);
	SudokuMatrixQt(SudokuMatrix sudokuMatrix, QWidget *parent = nullptr);

	SudokuMatrixQt *showCells();

	SudokuMatrixQt *iterateOverCellsQt(std::function<void(SudokuCellQt *)> function);

	~SudokuMatrixQt();
};

class SudokuCellQt : public QLabel {
	Q_OBJECT

      public:
	SudokuCellQt(SudokuCell &sudokuCell, QWidget *parent = nullptr);

	SudokuCell &cell;

	~SudokuCellQt();
};

#endif