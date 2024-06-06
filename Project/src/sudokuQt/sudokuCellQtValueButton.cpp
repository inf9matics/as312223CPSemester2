#include "sudokuQt.h"

SudokuCellQtValueButton::SudokuCellQtValueButton(SudokuCellQt &sudokuCellQt, int value, QWidget *parent) : sudokuCellQt(sudokuCellQt), value(value), QPushButton(parent) { this->connectTasks()->styleLayout()->setText(QString::number(this->value)); }

int SudokuCellQtValueButton::getValue() { return this->value; }

void SudokuCellQtValueButton::setCellQtValue() {
	this->sudokuCellQt.setValueQt(this->value);

	emit closeParent();
}

SudokuCellQtValueButton *SudokuCellQtValueButton::styleLayout() {
    QFont font;
    font.setWeight(QFont::Bold);
    this->setFont(font);

	this->setContentsMargins(0, 0, 0, 0);

	return this;
}

SudokuCellQtValueButton *SudokuCellQtValueButton::connectTasks() {
	QObject::connect(this, SIGNAL(clicked()), this, SLOT(setCellQtValue()));

    QObject::connect(this, SIGNAL(closeParent()), this->parent(), SLOT(closeDialog()));

	return this;
}