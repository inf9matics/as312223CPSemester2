#include "sudokuQt.h"

SudokuCellQtValueDialog::~SudokuCellQtValueDialog() {}

SudokuCellQtValueDialog::SudokuCellQtValueDialog(SudokuCellQt &sudokuCellQt, QWidget *parent) : QWidget(parent), buttonLayout(this), sudokuCellQt(sudokuCellQt) { this->styleLayout()->connectTasks(); }

void SudokuCellQtValueDialog::showDialog() {
	this->addMissingValues()->showValueButtons();
	this->move(this->parentWidget()->window()->pos() + this->parentWidget()->parentWidget()->pos() + this->parentWidget()->pos());
	this->setFixedSize(this->parentWidget()->width() * this->valueButtons.size(), this->parentWidget()->height());
	this->show();
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::styleLayout() {
	this->setWindowFlags(Qt::Popup);
	this->layout()->setSpacing(0);
	this->layout()->setContentsMargins(0, 0, 0, 0);
	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::iterateOverValueButtons(std::function<void(SudokuCellQtValueButton *)> function) {
	std::vector<SudokuCellQtValueButton *>::iterator valueButtonsIterator = this->valueButtons.begin();
	while (valueButtonsIterator != this->valueButtons.end()) {
		function(*valueButtonsIterator);
		valueButtonsIterator++;
	}

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::clearValues() {
	this->iterateOverValueButtons([this](QPushButton *valueButton) {
		this->buttonLayout.removeWidget(valueButton);
		delete (valueButton);
	});

	this->valueButtons.clear();

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::showValueButtons() {
	this->iterateOverValueButtons([](QPushButton *valueButton) { valueButton->show(); });

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::addValues(std::vector<int> values) {
	std::vector<int>::iterator valuesIterator = values.begin();
	while (valuesIterator != values.end()) {
		SudokuCellQtValueButton *valueButton = new SudokuCellQtValueButton{this->sudokuCellQt, *valuesIterator, this};
		this->valueButtons.push_back(valueButton);
		this->buttonLayout.addWidget(valueButton, this->valueButtonAlignment);
		valuesIterator++;
	}

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::addMissingValues() {
	std::vector<int> missingValues = this->sudokuCellQt.getMissingValues();
	missingValues.push_back(0);
	this->addValues(missingValues);
	return this;
}

void SudokuCellQtValueDialog::closeEvent(QCloseEvent *event) { emit closed(); }

SudokuCellQtValueDialog *SudokuCellQtValueDialog::connectTasks() {
	QObject::connect(this, SIGNAL(closed()), this, SLOT(closeDialog()));

	return this;
}

void SudokuCellQtValueDialog::closeDialog() {
	this->clearValues();
	this->close();
}