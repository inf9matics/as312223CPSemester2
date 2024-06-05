#include "sudokuQt.h"

SudokuCellQtValueDialog::~SudokuCellQtValueDialog() {}

SudokuCellQtValueDialog::SudokuCellQtValueDialog(SudokuCellQt &sudokuCellQt, QWidget *parent) : QWidget(parent), gridLayout(this), sudokuCellQt(sudokuCellQt) {}

void SudokuCellQtValueDialog::showDialog() { this->addMissingValues()->showValueButtons()->show(); }

SudokuCellQtValueDialog *SudokuCellQtValueDialog::styleLayout() { return this; }

SudokuCellQtValueDialog *SudokuCellQtValueDialog::iterateOverValueButtons(std::function<void(QPushButton *)> function) {
	std::vector<QPushButton *>::iterator valueButtonsIterator = this->valueButtons.begin();
	while (valueButtonsIterator != this->valueButtons.end()) {
		function(*valueButtonsIterator);
		valueButtonsIterator++;
	}

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::clearValues() {
	this->iterateOverValueButtons([this](QPushButton *valueButton) {
		this->gridLayout.removeWidget(valueButton);
		delete (valueButton);
	});

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::showValueButtons() {
	this->iterateOverValueButtons([](QPushButton *valueButton) { valueButton->show(); });

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::addValues(std::vector<int> values) {
	std::vector<int>::iterator valuesIterator = values.begin();
    int i{0};
	while (valuesIterator != values.end()) {
		QPushButton *valueButton = new QPushButton{this};
        valueButton->setText({QString::number(*valuesIterator)});
		this->valueButtons.push_back(valueButton);
		this->gridLayout.addWidget(this->valueButtons.back(), 0, i);

        i++;
		valuesIterator++;
	}

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::addMissingValues() {
	this->addValues(this->sudokuCellQt.getMissingValues());
	return this;
}