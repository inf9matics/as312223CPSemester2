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

class SudokuCellQtValueButton;

class SudokuMatrixQt : public QWidget, public SudokuMatrix {
	Q_OBJECT

      private:
	int cellFrameStyle{1};
	int cellSize{30};
	Qt::Alignment cellAlignment{Qt::AlignCenter};

      protected:
	std::vector<std::vector<SudokuCellQt *>> cellsQt;

	QGridLayout gridLayout;
	std::vector<QGridLayout *> subGridLayouts;

	SudokuMatrixQt *prepareCellsQt();
	SudokuMatrixQt *styleLayout();

	SudokuMatrixQt *styleCell(SudokuCellQt &sudokuCellQt);

	SudokuMatrixQt *iterateOverCellsQt(std::function<void(SudokuCellQt *)> function);
	SudokuMatrixQt *iterateOverSubGridLayouts(std::function<void(QGridLayout *)> function);

      public:
	SudokuMatrixQt(QWidget *parent = nullptr);
	SudokuMatrixQt(SudokuMatrix sudokuMatrix, QWidget *parent = nullptr);

	SudokuMatrixQt *showCells();

	SudokuCell *getCellAtPosition(std::pair<int, int> position);

	~SudokuMatrixQt();
};

class SudokuCellQt : public QLabel, public SudokuCell {
	Q_OBJECT

      private:
	SudokuCellQt *connectTasks();

	void mousePressEvent(QMouseEvent *event);

      protected:
	QPalette initialPalette;

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
	SudokuCellQtValueDialog *connectTasks();

	void closeEvent(QCloseEvent *event);

      private:
	SudokuCellQtValueDialog *styleLayout();

	SudokuCellQtValueDialog *showValueButtons();

	Qt::Alignment valueButtonAlignment{Qt::AlignCenter};

	QHBoxLayout buttonLayout;

      protected:
	std::vector<SudokuCellQtValueButton *> valueButtons;

	SudokuCellQt &sudokuCellQt;

	SudokuCellQtValueDialog *iterateOverValueButtons(std::function<void(SudokuCellQtValueButton *)> function);

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

class SudokuCellQtValueButton : public QPushButton {
	Q_OBJECT

      private:
	SudokuCellQtValueButton *connectTasks();

      private:
	SudokuCellQtValueButton *styleLayout();

      protected:
	SudokuCellQt &sudokuCellQt;

	int value;

      public:
	SudokuCellQtValueButton(SudokuCellQt &sudokuCellQt, int value, QWidget *parent = nullptr);

	int getValue();

      signals:
	void closeParent();

      public slots:
	void setCellQtValue();
};

#endif