#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSignalMapper>
#include <QSizePolicy>

#include <functional>

#include "gameLauncher.h"
#include "sudoku.h"

class SudokuCellQt;

class SudokuCellQtValueDialog;

class SudokuCellQtValueButton;

class SudokuSubMatrixQt;

class SudokuMatrixQt : public Game, public SudokuMatrix {
	Q_OBJECT

      private:
	SudokuMatrixQt *styleLayout();

      private:
	int cellFrameStyle{3};
	int cellSize{40};
	Qt::Alignment cellAlignment{Qt::AlignCenter};

	int subMatrixFrameStyle{3};
	Qt::Alignment subMatrixAlignment{Qt::AlignCenter};

	int subMatrixSpacing{0};
	QMargins subMatrixMargins{0, 0, 0, 0};

      protected:
	std::map<std::pair<int, int>, SudokuCellQt *> cellsQt;

	std::vector<std::vector<SudokuSubMatrixQt *>> subMatricesQt;

	QGridLayout gridLayout;

	SudokuMatrixQt *prepareCellsQt();
	SudokuMatrixQt *prepareSubMatricesQt();

	SudokuMatrixQt *prepareGridLayouts();

	SudokuMatrixQt *styleCell(SudokuCellQt &sudokuCellQt);
	SudokuMatrixQt *styleSubMatrix(SudokuSubMatrixQt &sudokuSubMatrixQt);

	SudokuMatrixQt *iterateOverCellsQt(std::function<void(SudokuCellQt *)> function);
	SudokuMatrixQt *iterateOverSubMatricesQt(std::function<void(SudokuSubMatrixQt *)> function);

      public:
	SudokuMatrixQt();
	SudokuMatrixQt(SudokuMatrix sudokuMatrix);

	SudokuMatrixQt &operator=(const SudokuMatrixQt &sudokuMatrixQt);

	SudokuMatrixQt *showCells();
	SudokuMatrixQt *showSubMatrices();
	SudokuMatrixQt *showBoard();

	SudokuCell *getCellAtPosition(std::pair<int, int> position);
	SudokuCellQt *getCellQtAtPosition(std::pair<int, int> position);

	~SudokuMatrixQt();

      public slots:
	void showGame();
};

class SudokuSubMatrixQt : public QFrame {
	Q_OBJECT

      private:
	SudokuSubMatrixQt *styleLayout();

      protected:
	QGridLayout gridLayout;

      public:
	SudokuSubMatrixQt(QWidget *parent = nullptr);

	SudokuSubMatrixQt &operator=(const SudokuSubMatrixQt &sudokuSubMatrixQt);

	SudokuSubMatrixQt *addCellToLayout(SudokuCellQt *sudokuCellQt, std::pair<int, int> position);
};

class SudokuCellQt : public QLabel, public SudokuCell {
	Q_OBJECT

      private:
	SudokuCellQt *connectTasks();

	void mousePressEvent(QMouseEvent *event);

      private:
	SudokuCellQt *styleLayout();

      protected:
	SudokuMatrixQt *parentMatrixQt;

	QPalette initialPalette;

	SudokuCellQtValueDialog *valueDialog;

	SudokuCellQt *iterateOverParityQt(std::function<void(SudokuCellQt *)> function);

      public:
	SudokuCellQt(std::pair<int, int> position, SudokuMatrixQt *parent = nullptr);
	SudokuCellQt(const SudokuCellQt &sudokuCellQt);

	SudokuCellQt &operator=(const SudokuCellQt &sudokuCellQt);
	SudokuCellQt &operator=(const SudokuCell &sudokuCell);

	SudokuCell *setValue(int value, bool checkParity = true);

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