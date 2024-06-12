#include "sudokuGame.h"

SudokuSubMatrixQt::SudokuSubMatrixQt(QWidget *parent) : QFrame(parent), gridLayout(this) { this->styleLayout(); }

SudokuSubMatrixQt *SudokuSubMatrixQt::styleLayout() {
	this->gridLayout.setSpacing(1);

    this->gridLayout.setContentsMargins(0, 0 ,0 ,0);

	return this;
}

SudokuSubMatrixQt *SudokuSubMatrixQt::addCellToLayout(SudokuCellQt *sudokuCellQt, std::pair<int, int> position) {
	this->gridLayout.addWidget(sudokuCellQt, position.second, position.first);

	return this;
}