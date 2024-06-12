#include "sudoku.h"

#include "moc_sudokuGame.cpp"

SudokuGame::~SudokuGame() {}

SudokuGame::SudokuGame(QWidget *parent) : GameLauncher(parent) {
	this->regenerateGame();

	this->prepareButtons();
	this->setSize();

	this->gameWindow->styleLayout();
}

SudokuGame::SudokuGame(SudokuMatrixQt *sudokuMatrixQt, QWidget *parent) : GameLauncher(parent) {
	this->game = sudokuMatrixQt;
	this->sudokuMatrixQt = sudokuMatrixQt;
	this->game->setGameLauncher(this);

	this->prepareButtons();
	this->setSize();

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

	QObject::connect(this->game, SIGNAL(gameEnded()), this, SLOT(spawnEndPopup()));

	return this;
}

void SudokuGame::regenerateGame() {
	SudokuMatrix matrixToSolve;

	SudokuBacksolver backsolver{&matrixToSolve};
	backsolver.solveMatrix();

	matrixToSolve.removeNoisyNumberOfCells(matrixToSolve.getSize() * matrixToSolve.getSubMatrixSize() * 1.5);

	delete this->game;
	SudokuMatrixQt *sudokuMatrixQt = new SudokuMatrixQt{matrixToSolve};
	this->game = sudokuMatrixQt;
	this->sudokuMatrixQt = sudokuMatrixQt;
	this->game->setGameLauncher(this);

	this->gameWindow->layout()->addWidget(this->game);
}

void SudokuGame::setBoardToFile() {
	std::string outputFilePath = QFileDialog::getSaveFileName(this, "Save to file").toStdString();
	if (outputFilePath == "") {
		return;
	}
	this->fileHandler.setSudokuMatrix(this->sudokuMatrixQt);
	this->fileHandler.setSudokuMatrixToFile(outputFilePath);
}

void SudokuGame::getBoardFromFile() {
	std::string inputFilePath = QFileDialog::getOpenFileName(this, "Save to file").toStdString();
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