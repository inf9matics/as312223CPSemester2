#ifndef SUDOKU_QT_H
#define SUDOKU_QT_H

#include <QGridLayout>
#include <QLabel>

#include <functional>

#include "sudoku.h"

class SudokuCellQt;

class SudokuMatrixQt : public QWidget, public SudokuMatrix {
	Q_OBJECT

      private:
	int cellFrameStyle{1};
	int cellSize{30};
	Qt::Alignment cellAlignment{Qt::AlignCenter};

      protected:
	std::vector<std::vector<SudokuCellQt *>> cellsQt;

	QGridLayout gridLayout;

	SudokuMatrixQt *prepareCellsQt();
	SudokuMatrixQt *styleLayout();

	SudokuMatrixQt *styleCell(SudokuCellQt &sudokuCellQt);

      public:
	SudokuMatrixQt(QWidget *parent = nullptr);
	SudokuMatrixQt(SudokuMatrix sudokuMatrix, QWidget *parent = nullptr);

	SudokuMatrixQt *showCells();

	SudokuCell *getCellAtPosition(std::pair<int, int> position);

	SudokuMatrixQt *iterateOverCellsQt(std::function<void(SudokuCellQt *)> function);

	~SudokuMatrixQt();
};

class SudokuCellQt : public QLabel, public SudokuCell {
	Q_OBJECT

      protected:
	void mousePressEvent(QMouseEvent *event);

	SudokuCellQt *connectTasks();

      public:
	SudokuCellQt(std::pair<int, int> position, QWidget *parent = nullptr);

	SudokuCellQt *setValue(int value);

	~SudokuCellQt();

      signals:

	void clicked();
	void valueChanged();

	public slots:

	void updateValue(int value);
};

#endif