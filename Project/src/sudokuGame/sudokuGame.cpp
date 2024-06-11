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
	this->game->setGameLauncher(this);

	this->prepareButtons();
	this->setSize();

	this->gameWindow->styleLayout();
}

GameLauncher *SudokuGame::prepareButtons() {
	this->generateMenuButton("Start game");
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this->game, SLOT(gameStart()));
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this, SLOT(showGameWindow()));

	this->gameWindow->generateMenuButton("Back to menu");
	QObject::connect(this->gameWindow->getMenuButtonsBack(), SIGNAL(clicked()), this, SLOT(showGameLauncher()));
	this->gameWindow->generateMenuButton("Regenerate board");
	QObject::connect(this->gameWindow->getMenuButtonsBack(), SIGNAL(clicked()), this, SLOT(regenerateGame()));

	this->gameWindow->addFinalStretch();

	return this;
}

void SudokuGame::regenerateGame() {
	delete this->game;
	this->game = new SudokuMatrixQt{};
	this->game->setGameLauncher(this);

	this->gameWindow->styleLayout();
}