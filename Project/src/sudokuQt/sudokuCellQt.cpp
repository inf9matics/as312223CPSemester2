#include "sudokuQt.h"

SudokuCellQt::~SudokuCellQt() {}

SudokuCellQt::SudokuCellQt(std::pair<int, int> position, QWidget *parent) : QLabel(parent), SudokuCell(position) {
	this->valueDialog = new SudokuCellQtValueDialog(*this, this);
	this->connectTasks();
}

SudokuCellQt::SudokuCellQt(const SudokuCellQt &sudokuCellQt) : SudokuCell(sudokuCellQt) {
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

	return this;
}

SudokuCellQt *SudokuCellQt::operator=(const SudokuCellQt &sudokuCellQt) {
	this->position = sudokuCellQt.position;

	this->value = sudokuCellQt.value;
	this->previousValue = sudokuCellQt.value;

	this->viable = sudokuCellQt.viable;

	this->QLabel::setParent(sudokuCellQt.parentWidget());

	return this;
}

void SudokuCellQt::mousePressEvent(QMouseEvent *event) { emit clicked(); }

SudokuCellQt *SudokuCellQt::setValue(int value) {
	this->SudokuCell::setValue(value);
	this->setNum(this->value);

	emit valueChanged();

	return this;
}

void SudokuCellQt::setValueQt(int value) { this->SudokuCellQt::setValue(value); }

void SudokuCellQt::updateViableColor() {
	QPalette palette = this->palette();
	if (this->viable) {
		palette.setColor(this->foregroundRole(), {255, 255, 255});
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