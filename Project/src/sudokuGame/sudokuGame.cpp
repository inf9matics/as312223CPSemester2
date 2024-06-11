#include "sudoku.h"

#include "moc_sudokuGame.cpp"

SudokuGame::~SudokuGame() {}

SudokuGame::SudokuGame(QWidget *parent) : GameLauncher(new SudokuMatrixQt{}, parent) { this->game->setGameWindow(this->gameWindow); }

SudokuGame::SudokuGame(SudokuMatrixQt *sudokuMatrixQt, QWidget *parent) : game(sudokuMatrixQt), GameLauncher(sudokuMatrixQt, parent) {
	this->menuButtons.push_back(new QPushButton(this));
	this->menuButtonsLayout.addWidget(this->menuButtons.back());
	this->menuButtons.back()->setText("Start game");
    QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this->game, SLOT(gameStart()));
}