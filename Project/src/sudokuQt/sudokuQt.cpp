#include "sudokuQt.h"

SudokuMatrixQt::~SudokuMatrixQt() {}

SudokuMatrixQt::SudokuMatrixQt(QWidget *parent) : QWidget(parent), gridLayout(this), SudokuMatrix() { this->prepareCellsQt()->styleLayout(); }

SudokuMatrixQt::SudokuMatrixQt(SudokuMatrix sudokuMatrix, QWidget *parent) : QWidget(parent), gridLayout(this), SudokuMatrix(sudokuMatrix) {
	this->prepareCellsQt()->styleLayout();

	this->iterateOverCellsQt([&sudokuMatrix](SudokuCellQt *sudokuCellQt) { sudokuCellQt->setValue(sudokuMatrix.getCellAtPosition(sudokuCellQt->getPosition())->getValue()); });
}

SudokuMatrixQt *SudokuMatrixQt::prepareCellsQt() {
	for (int i{0}; i < this->SudokuMatrix::size; i++) {
		std::vector<SudokuCellQt *> row;
		for (int j{0}; j < this->SudokuMatrix::size; j++) {
			SudokuCellQt *cellQt = new SudokuCellQt{std::pair<int, int>{i, j}, this->parentWidget()};
			cellQt->SudokuCell::setParent(this);
			this->styleCell(*cellQt);
			row.emplace_back(cellQt);
			this->gridLayout.addWidget(cellQt, i, j);
		}
		this->cellsQt.push_back(row);
	}

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::styleLayout() {
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

SudokuCell *SudokuMatrixQt::getCellAtPosition(std::pair<int, int> position) { return &this->cells.at(position.first).at(position.second); }

SudokuCellQt::~SudokuCellQt() {}

SudokuCellQt::SudokuCellQt(std::pair<int, int> position, QWidget *parent) : QLabel(parent), SudokuCell(position) { this->connectTasks(); }

void SudokuCellQt::mousePressEvent(QMouseEvent *event) { emit clicked(); }

SudokuCellQt *SudokuCellQt::setValue(int value) {
	this->SudokuCell::setValue(value);

	emit valueChanged();

	return this;
}

void SudokuCellQt::updateValue(int value) { this->setValue(value); }

SudokuCellQt *SudokuCellQt::connectTasks() {
	connect(this, SIGNAL(valueChanged()), this, SLOT(setNum(int)));

	connect(this, SIGNAL(clicked()), this, SLOT(updateValue(int value)));

	return this;
}