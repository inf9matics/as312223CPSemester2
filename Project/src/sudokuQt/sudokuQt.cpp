#include "sudokuQt.h"

SudokuMatrixQt::~SudokuMatrixQt() {}

SudokuMatrixQt::SudokuMatrixQt(QWidget *parent) : QTableWidget(parent), SudokuMatrix() {}

SudokuCellQt::~SudokuCellQt() {}

SudokuCellQt::SudokuCellQt(std::pair<int, int> position) : QTableWidgetItem(), SudokuCell(position) {}