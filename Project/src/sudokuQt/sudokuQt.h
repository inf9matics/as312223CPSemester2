#ifndef SUDOKU_QT_H
#define SUDOKU_QT_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSignalMapper>
#include <QSizePolicy>

#include <functional>

#include "sudoku.h"

class SudokuCellQt;

class SudokuCellQtValueDialog;

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

	SudokuCellQtValueDialog *valueDialog;

      public:
	SudokuCellQt(std::pair<int, int> position, QWidget *parent = nullptr);
	SudokuCellQt(const SudokuCellQt &sudokuCellQt);

	SudokuCellQt *operator=(const SudokuCellQt &sudokuCellQt);
	SudokuCellQt *operator=(const SudokuCell &sudokuCell);

	SudokuCellQt *setValue(int value);

	~SudokuCellQt();

      signals:

	void clicked();
	void valueChanged();

      public slots:

	void setValueQt(int value);
	void updateViableColor();
};

class SudokuCellQtValueDialog : public QWidget {
	Q_OBJECT

      private:
	Qt::Alignment valueButtonAlignment{Qt::AlignCenter};

	void closeEvent(QCloseEvent *event);

	SudokuCellQtValueDialog *connectTasks();

      protected:
	std::vector<QPushButton *> valueButtons;

	SudokuCellQt &sudokuCellQt;

	QHBoxLayout buttonLayout;

	SudokuCellQtValueDialog *styleLayout();

	SudokuCellQtValueDialog *showValueButtons();

	SudokuCellQtValueDialog *iterateOverValueButtons(std::function<void(QPushButton *)> function);

      public:
	SudokuCellQtValueDialog(SudokuCellQt &sudokuCellQt, QWidget *parent = nullptr);

	~SudokuCellQtValueDialog();

	SudokuCellQtValueDialog *addValues(std::vector<int> values);
	SudokuCellQtValueDialog *addMissingValues();
	SudokuCellQtValueDialog *clearValues();

      signals:
	void closed();

      public slots:

	void showDialog();
	void closeDialog();
};

#endif