#include "sudokuQt.h"

SudokuMatrixQt::~SudokuMatrixQt() {
	this->iterateOverCellsQt([](SudokuCellQt *sudokuCellQt) { delete(sudokuCellQt); });
	this->iterateOverSubGridLayouts([](QGridLayout *subGridLayout) { delete(subGridLayout); });
}

SudokuMatrixQt::SudokuMatrixQt(QWidget *parent) : QWidget(parent), gridLayout(this), SudokuMatrix() {
	this->prepareCellsQt()->styleLayout()->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });
}

SudokuMatrixQt::SudokuMatrixQt(SudokuMatrix sudokuMatrix, QWidget *parent) : QWidget(parent), gridLayout(this), SudokuMatrix(sudokuMatrix) {
	this->prepareCellsQt()->styleLayout()->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });
}

SudokuMatrixQt *SudokuMatrixQt::iterateOverSubGridLayouts(std::function<void(QGridLayout *)> function) {
	std::vector<QGridLayout *>::iterator subGridLayoutsIterator = this->subGridLayouts.begin();
	while(subGridLayoutsIterator != this->subGridLayouts.end()) {
		function(*subGridLayoutsIterator);
		subGridLayoutsIterator++;
	}

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::prepareCellsQt() {
	for (int i{0}; i < this->SudokuMatrix::size; i++) {
		std::vector<SudokuCellQt *> row;
		for (int j{0}; j < this->SudokuMatrix::size; j++) {
			SudokuCellQt *cellQt = new SudokuCellQt{std::pair<int, int>{i, j}, this};
			*cellQt = this->cells.at(i).at(j);
			cellQt->SudokuCell::setParent(this);
			this->styleCell(*cellQt);
			row.emplace_back(cellQt);
		}
		this->cellsQt.push_back(row);
	}

	this->iterateOverCellsQt([this](SudokuCellQt *sudokuCellQt) { sudokuCellQt->setValue(sudokuCellQt->getValue()); });

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::styleLayout() {
	for (int i{0}; i < this->subMatrixSize; i++) {
		for (int j{0}; j < this->subMatrixSize; j++) {
			QGridLayout *subGridLayout = new QGridLayout;
			this->subGridLayouts.push_back(subGridLayout);
			for(int k{0}; k < this->subMatrixSize; k++) {
				for(int l{0}; l < this->subMatrixSize; l++) {
					subGridLayout->addWidget(this->cellsQt.at((i * this->subMatrixSize) + k).at((j * this->subMatrixSize) + l), (i * this->subMatrixSize) + k, (j * this->subMatrixSize) + l);
				}
			}
			this->gridLayout.addLayout(subGridLayout, i, j);
		}
	}

	this->setWindowTitle("sudokuBoard");

	this->gridLayout.setHorizontalSpacing(1);
	this->gridLayout.setVerticalSpacing(1);

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::styleCell(SudokuCellQt &sudokuCellQt) {
	sudokuCellQt.setFrameStyle(this->cellFrameStyle);

	sudokuCellQt.setFixedSize(this->cellSize, this->cellSize);

	sudokuCellQt.setAlignment(this->cellAlignment);

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::showCells() {
	this->iterateOverCellsQt([](SudokuCellQt *sudokuCellQt) { sudokuCellQt->show(); });

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::iterateOverCellsQt(std::function<void(SudokuCellQt *)> function) {
	std::vector<std::vector<SudokuCellQt *>>::iterator columnIterator = this->cellsQt.begin();
	while (columnIterator != this->cellsQt.end()) {
		std::vector<SudokuCellQt *>::iterator rowIterator = columnIterator->begin();
		while (rowIterator != columnIterator->end()) {
			function(*rowIterator);
			rowIterator++;
		}
		columnIterator++;
	}

	return this;
}

SudokuCell *SudokuMatrixQt::getCellAtPosition(std::pair<int, int> position) { return this->cellsQt.at(position.first).at(position.second); }
