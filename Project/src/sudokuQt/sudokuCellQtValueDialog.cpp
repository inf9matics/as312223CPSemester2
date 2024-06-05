#include "sudokuQt.h"

SudokuCellQtValueDialog::~SudokuCellQtValueDialog() {}

SudokuCellQtValueDialog::SudokuCellQtValueDialog(SudokuCellQt &sudokuCellQt, QWidget *parent) : QWidget(parent), buttonLayout(this), sudokuCellQt(sudokuCellQt) { this->styleLayout()->connectTasks(); }

void SudokuCellQtValueDialog::showDialog() { this->addMissingValues()->showValueButtons()->show(); }

SudokuCellQtValueDialog *SudokuCellQtValueDialog::styleLayout() {
	this->setWindowFlags(Qt::Popup);
	return this;
}

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
	int i{0};
	while (valuesIterator != values.end()) {
		QPushButton *valueButton = new QPushButton{this};
		this->valueButtons.push_back(valueButton);
		valueButton->setText(QString::number(*valuesIterator));
		this->buttonLayout.addWidget(this->valueButtons.back(), this->valueButtonAlignment);

		i++;
		valuesIterator++;
	}

	return this;
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::addMissingValues() {
	this->addValues(this->sudokuCellQt.getMissingValues());
	return this;
}

void SudokuCellQtValueDialog::closeEvent(QCloseEvent *event) {
    this->close();
    emit closed();
}

SudokuCellQtValueDialog *SudokuCellQtValueDialog::connectTasks() {
    QObject::connect(this, SIGNAL(closed()), this, SLOT(closeDialog()));

    return this;
}

void SudokuCellQtValueDialog::closeDialog() {
    this->clearValues();
}