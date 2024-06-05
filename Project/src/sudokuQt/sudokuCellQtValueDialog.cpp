#include "sudokuQt.h"

SudokuCellQtValueDialog::~SudokuCellQtValueDialog() {}

SudokuCellQtValueDialog::SudokuCellQtValueDialog(SudokuCellQt &sudokuCellQt, QWidget *parent) : QWidget(parent), sudokuCellQt(sudokuCellQt) {}

void SudokuCellQtValueDialog::showDialog() { this->show(); }