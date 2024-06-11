#include "sudoku.h"

#include "moc_sudokuGame.cpp"

SudokuGame::~SudokuGame() {}

SudokuGame::SudokuGame(QWidget *parent) : GameLauncher(this->game, parent) {
	SudokuMatrixQt *sudokuMatrixQt = new SudokuMatrixQt{};
	this->game = sudokuMatrixQt;
	this->game->QWidget::setParent(this);
	this->game->setGameWindow(this->gameWindow);

	this->menuButtons.push_back(new QPushButton(this));
	this->menuButtonsLayout.addWidget(this->menuButtons.back());
	this->menuButtons.back()->setText("Start game");
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this->game, SLOT(gameStart()));
}

SudokuGame::SudokuGame(SudokuMatrixQt *sudokuMatrixQt, QWidget *parent) : game(sudokuMatrixQt), GameLauncher(sudokuMatrixQt, parent) {
	this->menuButtons.push_back(new QPushButton(this));
	this->menuButtonsLayout.addWidget(this->menuButtons.back());
	this->menuButtons.back()->setText("Start game");
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this->game, SLOT(gameStart()));
}