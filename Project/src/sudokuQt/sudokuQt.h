#ifndef SUDOKU_QT_H
#define SUDOKU_QT_H

#include <QTableWidget>
#include <QTableWidgetItem>

#include "sudoku.h"

class SudokuMatrixQt : public QTableWidget, public SudokuMatrix {
	Q_OBJECT

      public:
	SudokuMatrixQt(QWidget *parent = nullptr);

	~SudokuMatrixQt();
};

class SudokuCellQt : public QTableWidgetItem, public SudokuCell {
	Q_OBJECT

      public:
	SudokuCellQt(std::pair<int, int> position);

	~SudokuCellQt();
};

#endif