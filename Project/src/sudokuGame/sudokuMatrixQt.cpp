#include "sudokuGame.h"

SudokuMatrixQt::~SudokuMatrixQt() {
	this->iterateOverCellsQt([](SudokuCellQt *sudokuCellQt) { delete (sudokuCellQt); });
	this->iterateOverSubMatricesQt([](SudokuSubMatrixQt *sudokuSubMatrixQt) { delete (sudokuSubMatrixQt); });
}

SudokuMatrixQt::SudokuMatrixQt() : gridLayout(this), SudokuMatrix() {
	this->displayName = "Sudoku";

	this->prepareCellsQt()->prepareSubMatricesQt()->prepareGridLayouts()->styleLayout()->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });
}

SudokuMatrixQt::SudokuMatrixQt(SudokuMatrix sudokuMatrix) : gridLayout(this), SudokuMatrix(sudokuMatrix) {
	this->displayName = "Sudoku";

	this->prepareCellsQt()->prepareSubMatricesQt()->prepareGridLayouts()->styleLayout()->iterateOverSubMatrices([this](SudokuSubMatrix *sudokuSubMatrix) { sudokuSubMatrix->setParent(this); });
}

SudokuMatrixQt *SudokuMatrixQt::iterateOverSubMatricesQt(std::function<void(SudokuSubMatrixQt *)> function) {
	std::vector<std::vector<SudokuSubMatrixQt *>>::iterator rowIterator = this->subMatricesQt.begin();
	while (rowIterator != this->subMatricesQt.end()) {
		std::vector<SudokuSubMatrixQt *>::iterator columnIterator = rowIterator->begin();
		while (columnIterator != rowIterator->end()) {
			function(*columnIterator);
			columnIterator++;
		}
		rowIterator++;
	}

	return this;
}

SudokuMatrixQt &SudokuMatrixQt::operator=(const SudokuMatrix &sudokuMatrix) {
	SudokuMatrix currentMatrix{sudokuMatrix};
	this->iterateOverCellsQt([this, &currentMatrix](SudokuCellQt *sudokuCellQt) {
		sudokuCellQt->setValue(currentMatrix.getCellAtPosition(sudokuCellQt->getPosition())->getValue());
		if (currentMatrix.getCellAtPosition(sudokuCellQt->getPosition())->getLocked()) {
			sudokuCellQt->lock();
		}
	});

	return *this;
}

void SudokuMatrixQt::showGame() { this->showBoard(); }

SudokuMatrixQt *SudokuMatrixQt::showBoard() {
	this->showCells()->showSubMatrices()->show();

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::showSubMatrices() {
	this->iterateOverSubMatricesQt([](SudokuSubMatrixQt *sudokuSubMatrixQt) { sudokuSubMatrixQt->show(); });

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::prepareCellsQt() {
	for (int i{0}; i < this->SudokuMatrix::size; i++) {
		for (int j{0}; j < this->SudokuMatrix::size; j++) {
			SudokuCellQt *cellQt = new SudokuCellQt{std::pair<int, int>{i, j}, this};
			*cellQt = *this->SudokuMatrix::getCellAtPosition({i, j});
			cellQt->SudokuCell::setParent(this);

			this->cellsQt.insert({{i, j}, cellQt});
		}
	}

	this->iterateOverCellsQt([this](SudokuCellQt *sudokuCellQt) { sudokuCellQt->setValue(sudokuCellQt->getValue()); });

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::prepareSubMatricesQt() {
	for (int i{0}; i < this->subMatrixSize; i++) {
		std::vector<SudokuSubMatrixQt *> row;
		for (int j{0}; j < this->subMatrixSize; j++) {
			SudokuSubMatrixQt *subMatrixQt = new SudokuSubMatrixQt(this);
			row.push_back(subMatrixQt);
			for (int k{0}; k < this->subMatrixSize; k++) {
				for (int l{0}; l < this->subMatrixSize; l++) {
					SudokuCellQt *cellQt = this->getCellQtAtPosition({(i * this->subMatrixSize) + k, (j * this->subMatrixSize) + l});

					subMatrixQt->addCellToLayout(cellQt, std::pair<int, int>{k, l});
					cellQt->QObject::setParent(subMatrixQt);
				}
			}
		}
		this->subMatricesQt.push_back(row);
	}

	return this;
}

SudokuMatrixQt &SudokuMatrixQt::operator=(const SudokuMatrixQt &sudokuMatrixQt) {
	(SudokuMatrix) *this = (SudokuMatrix)sudokuMatrixQt;

	this->cellsQt = sudokuMatrixQt.cellsQt;

	return *this;
}

SudokuMatrixQt *SudokuMatrixQt::prepareGridLayouts() {
	for (int i{0}; i < this->subMatrixSize; i++) {
		for (int j{0}; j < this->subMatrixSize; j++) {
			this->gridLayout.addWidget(this->subMatricesQt.at(i).at(j), j, i);
		}
	}

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::styleLayout() {
	this->setWindowTitle("sudokuBoard");

	this->setFixedSize(this->cellSize * this->SudokuMatrix::size, this->cellSize * this->SudokuMatrix::size);

	this->gridLayout.setSpacing(this->subMatrixSpacing);
	this->gridLayout.setContentsMargins(this->subMatrixMargins);

	this->iterateOverCellsQt([this](SudokuCellQt *sudokuCellQt) { this->styleCell(*sudokuCellQt); });
	this->iterateOverSubMatricesQt([this](SudokuSubMatrixQt *sudokuSubMatrixQt) { this->styleSubMatrix(*sudokuSubMatrixQt); });

	this->setFixedSize({this->SudokuMatrix::subMatrixSize * (this->cellSize * this->subMatrixSize), this->SudokuMatrix::subMatrixSize * (this->cellSize * this->subMatrixSize)});

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::styleCell(SudokuCellQt &sudokuCellQt) {
	sudokuCellQt.setFrameStyle(this->cellFrameStyle);
	sudokuCellQt.setLineWidth(this->cellFrameWidth);

	sudokuCellQt.setFixedSize(this->cellSize, this->cellSize);

	sudokuCellQt.setAlignment(this->cellAlignment);

	if (sudokuCellQt.getLocked()) {
		QFont font = sudokuCellQt.font();
		font.setWeight(QFont::Bold);
		sudokuCellQt.setFont(font);
	}

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::styleSubMatrix(SudokuSubMatrixQt &sudokuSubMatrixQt) {
	sudokuSubMatrixQt.setFrameStyle(this->subMatrixFrameStyle);
	sudokuSubMatrixQt.setLineWidth(this->subMatrixFrameWidth);

	sudokuSubMatrixQt.setFixedSize(this->cellSize * this->subMatrixSize, this->cellSize * this->subMatrixSize);

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::showCells() {
	this->iterateOverCellsQt([](SudokuCellQt *sudokuCellQt) { sudokuCellQt->show(); });

	return this;
}

SudokuMatrixQt *SudokuMatrixQt::iterateOverCellsQt(std::function<void(SudokuCellQt *)> function) {
	std::map<std::pair<int, int>, SudokuCellQt *>::iterator cellsQtIterator = this->cellsQt.begin();
	while (cellsQtIterator != this->cellsQt.end()) {
		function(cellsQtIterator->second);
		cellsQtIterator++;
	}

	return this;
}

SudokuCell *SudokuMatrixQt::getCellAtPosition(std::pair<int, int> position) { return this->cellsQt.at(position); }

SudokuCellQt *SudokuMatrixQt::getCellQtAtPosition(std::pair<int, int> position) { return this->cellsQt.at(position); }

void SudokuMatrixQt::checkIfWon() {
	if (this->viable && this->filled) {
		this->won = true;

		this->gameEnd();
	}
}

bool SudokuMatrixQt::checkFilled() {
	bool filled{true};
	this->iterateOverCellsQt([&filled](SudokuCellQt *sudokuCellQt) {
		if (filled && sudokuCellQt->getValue() == 0) {
			filled = false;
		}
	});

	this->filled = filled;
	return this->filled;
}