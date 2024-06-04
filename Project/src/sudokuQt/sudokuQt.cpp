#include "sudokuQt.h"

SudokuMatrixQt::~SudokuMatrixQt() {}

SudokuMatrixQt::SudokuMatrixQt(QWidget *parent) : QGridLayout(parent), SudokuMatrix() {
    for(int i{0}; i < this->size; i++) {
        std::vector<SudokuCellQt *> row;
        for(int j{0}; j < this->size; j++) {
            SudokuCellQt *cellQt = new SudokuCellQt{*this->getCellAtPosition(std::pair<int, int>{i, j}), this->parentWidget()};
            row.emplace_back(cellQt);
            this->addWidget(cellQt);
        }
        this->cellsQt.push_back(row);
    }
}

SudokuMatrixQt::SudokuMatrixQt(SudokuMatrix sudokuMatrix, QWidget *parent) : QGridLayout(parent), SudokuMatrix(sudokuMatrix) {
    for(int i{0}; i < this->size; i++) {
        std::vector<SudokuCellQt *> row;
        for(int j{0}; j < this->size; j++) {
            SudokuCellQt *cellQt = new SudokuCellQt{*this->getCellAtPosition(std::pair<int, int>{i, j}), this->parentWidget()};
            row.emplace_back(cellQt);
            this->addWidget(cellQt);
        }
        this->cellsQt.push_back(row);
    }
}

SudokuMatrixQt *SudokuMatrixQt::showCells() {
    this->iterateOverCellsQt([](SudokuCellQt *sudokuCellQt) {sudokuCellQt->show();});

    return this;
}

SudokuMatrixQt *SudokuMatrixQt::iterateOverCellsQt(std::function<void(SudokuCellQt *)> function) {
    std::vector<std::vector<SudokuCellQt *>>::iterator columnIterator = this->cellsQt.begin();
    while(columnIterator != this->cellsQt.end()) {
        std::vector<SudokuCellQt *>::iterator rowIterator = columnIterator->begin();
        while(rowIterator != columnIterator->end()) {
            function(*rowIterator);
            rowIterator++;
        }
        columnIterator++;
    }

    return this;
}

SudokuCellQt::~SudokuCellQt() {}

SudokuCellQt::SudokuCellQt(SudokuCell &sudokuCell, QWidget *parent) : QWidget(parent), cell(sudokuCell) {}