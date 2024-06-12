#include "sudoku.h"

#include "moc_sudokuGame.cpp"

SudokuGame::~SudokuGame() {}

SudokuGame::SudokuGame(QWidget *parent) : GameLauncher(parent) {
	SudokuMatrixQt *sudokuMatrixQt = new SudokuMatrixQt{};
	this->game = sudokuMatrixQt;
	this->sudokuMatrixQt = sudokuMatrixQt;
	this->game->setGameLauncher(this);

	this->prepareButtons();
	this->setSize();

	this->setWindowTitle("Sudoku");

	this->gameWindow->styleLayout();
}

SudokuGame::SudokuGame(SudokuMatrixQt *sudokuMatrixQt, QWidget *parent) : GameLauncher(parent) {
	this->game = sudokuMatrixQt;
	this->sudokuMatrixQt = sudokuMatrixQt;
	this->game->setGameLauncher(this);

	this->prepareButtons();
	this->setSize();

	this->setWindowTitle("Sudoku");

	this->gameWindow->styleLayout();
}

GameLauncher *SudokuGame::prepareButtons() {
	this->generateMenuButton("Start game");
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this->game, SLOT(gameStart()));
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this, SLOT(gameStartTime()));
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this, SLOT(regenerateGame()));
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this, SLOT(showGameWindow()));
	this->generateMenuButton("Read board");
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this->game, SLOT(gameStart()));
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this, SLOT(gameStartTime()));
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this, SLOT(showGameWindow()));
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this, SLOT(getBoardFromFile()));

	this->gameWindow->generateMenuButton("Back to menu");
	QObject::connect(this->gameWindow->getMenuButtonsBack(), SIGNAL(clicked()), this, SLOT(showGameLauncher()));
	QObject::connect(this->gameWindow->getMenuButtonsBack(), SIGNAL(clicked()), this, SLOT(gameEndTime()));
	this->gameWindow->generateMenuButton("Regenerate board");
	QObject::connect(this->gameWindow->getMenuButtonsBack(), SIGNAL(clicked()), this, SLOT(regenerateGame()));
	this->gameWindow->generateMenuButton("Write board");
	QObject::connect(this->gameWindow->getMenuButtonsBack(), SIGNAL(clicked()), this, SLOT(setBoardToFile()));

	this->gameWindow->addFinalStretch();

	this->gameVarianceSlider = new QSlider{Qt::Horizontal, this->gameWindow->menuBar};
	this->gameVarianceSlider->setMinimum(0);
	this->gameVarianceSlider->setMaximum(std::pow(this->sudokuMatrixQt->SudokuMatrix::getSize(), 2));
	this->gameVarianceSlider->setValue((std::pow(this->sudokuMatrixQt->SudokuMatrix::getSize(), 2) * 3) / 4);
	this->gameWindow->menuBarLayout.addWidget(this->gameVarianceSlider, 0, Qt::AlignRight);
	this->gameVarianceSlider->setFixedWidth(this->gameWindow->menuButtonWidthPerLetter * 12);
	this->gameVarianceSlider->setFixedHeight(this->gameWindow->menuButtonHeight);

	QObject::connect(this->game, SIGNAL(gameEnded()), this, SLOT(spawnEndPopup()));

	return this;
}

void SudokuGame::regenerateGame() {
	SudokuMatrix matrixToSolve;

	SudokuBacksolver backsolver{&matrixToSolve};
	backsolver.solveMatrix();

	matrixToSolve.removeNumberOfCells(this->gameVarianceSlider->value());
	matrixToSolve.lockFilled();

	delete this->game;
	SudokuMatrixQt *sudokuMatrixQt = new SudokuMatrixQt{matrixToSolve};
	this->game = sudokuMatrixQt;
	this->sudokuMatrixQt = sudokuMatrixQt;
	this->game->setGameLauncher(this);

	this->gameWindow->layout()->addWidget(this->game);
}

void SudokuGame::setBoardToFile() {
	std::string outputFilePath = QFileDialog::getSaveFileName(this, "Save to file", "", "*.json").toStdString();
	if (outputFilePath == "") {
		return;
	}
	this->fileHandler.setSudokuMatrix(this->sudokuMatrixQt);
	this->fileHandler.setSudokuMatrixToFile(outputFilePath);
}

void SudokuGame::getBoardFromFile() {
	std::string inputFilePath = QFileDialog::getOpenFileName(this, "Read from file", "", "*.json").toStdString();
	if (inputFilePath == "") {
		return;
	}

	delete this->game;
	SudokuMatrixQt *sudokuMatrixQt = new SudokuMatrixQt{this->fileHandler.getSudokuMatrixFromFile(inputFilePath)};
	this->game = sudokuMatrixQt;
	this->sudokuMatrixQt = sudokuMatrixQt;
	this->game->setGameLauncher(this);

	this->gameWindow->layout()->addWidget(this->game);
}