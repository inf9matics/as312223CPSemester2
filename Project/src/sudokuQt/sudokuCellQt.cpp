#include "sudokuQt.h"

SudokuCellQt::~SudokuCellQt() {}

SudokuCellQt::SudokuCellQt(std::pair<int, int> position, SudokuMatrixQt *parent) : QLabel(parent), SudokuCell(position), parentMatrixQt(parent), initialPalette(this->palette()) {
	this->valueDialog = new SudokuCellQtValueDialog(*this, this);
	this->connectTasks();
}

SudokuCellQt::SudokuCellQt(const SudokuCellQt &sudokuCellQt) : SudokuCell(sudokuCellQt), initialPalette(this->palette()) {
	*this = sudokuCellQt;

	this->valueDialog = new SudokuCellQtValueDialog(*this, this);
	this->connectTasks();
}

SudokuCellQt *SudokuCellQt::operator=(const SudokuCell &sudokuCell) {
	SudokuCell cell{sudokuCell};

	this->position = cell.getPosition();

	this->value = cell.getValue();
	this->previousValue = cell.getPreviousValue();

	this->viable = cell.getViable();

	this->parityCells = cell.getParityCells();

	return this;
}

SudokuCellQt *SudokuCellQt::operator=(const SudokuCellQt &sudokuCellQt) {
	this->position = sudokuCellQt.position;

	this->value = sudokuCellQt.value;
	this->previousValue = sudokuCellQt.value;

	this->viable = sudokuCellQt.viable;

	this->parityCells = sudokuCellQt.parityCells;

	this->QLabel::setParent(sudokuCellQt.parentWidget());

	return this;
}

void SudokuCellQt::mousePressEvent(QMouseEvent *event) { emit clicked(); }

SudokuCellQt *SudokuCellQt::iterateOverParityQt(std::function<void(SudokuCellQt *)> function) {
	std::vector<std::pair<int, int>>::iterator parityCellsIterator = this->parityCells.begin();
	while (parityCellsIterator != this->parityCells.end()) {
		if (!this->parentMatrixQt->getCellQtAtPosition(*parityCellsIterator)->getCalledParity()) {
			function(this->parentMatrixQt->getCellQtAtPosition(*parityCellsIterator));
		}
		parityCellsIterator++;
	}

	return this;
}

SudokuCell *SudokuCellQt::setValue(int value, bool checkParity) {
	if (value <= this->parentMatrix->getSize()) {
		this->SudokuCell::setValue(value, false);

		this->setNum(value);

		if (checkParity && !this->parityCells.empty()) {
			this->calledParity = true;
			this->iterateOverParityQt([value](SudokuCellQt *sudokuCellQt) { sudokuCellQt->setValue(value); });
			this->calledParity = false;

			this->viable = this->parentMatrix->checkViableAtPosition(this->position);
		}

		emit valueChanged();
	}

	return this;
}

void SudokuCellQt::setValueQt(int value) { this->SudokuCellQt::setValue(value); }

void SudokuCellQt::updateViableColor() {
	QPalette palette = this->palette();
	if (this->viable) {
		palette = this->initialPalette;
	} else {
		palette.setColor(this->foregroundRole(), {255, 0, 0});
	}

	this->setPalette(palette);
}

SudokuCellQt *SudokuCellQt::connectTasks() {
	QObject::connect(this, SIGNAL(valueChanged()), this, SLOT(updateViableColor()));

	QObject::connect(this, SIGNAL(clicked()), this->valueDialog, SLOT(showDialog()));

	return this;
}

SudokuCellQt *SudokuCellQt::styleLayout() {
	QSizePolicy sizePolicy{};
	sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
	this->setSizePolicy(sizePolicy);

	return this;
}