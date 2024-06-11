#include "sudoku.h"

#include "moc_sudokuGame.cpp"

SudokuGame::~SudokuGame() {}

SudokuGame::SudokuGame(QWidget *parent) : GameLauncher(parent) {
	this->game = new SudokuMatrixQt{};
	this->game->setGameLauncher(this);

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
	this->menuButtons.push_back(new QPushButton(this->menuBar));
	this->menuButtonsLayout.addWidget(this->menuButtons.back(), 0, this->menuButtonAlignment);
	this->menuButtons.back()->setText("Start game");
	this->menuButtons.back()->setFixedSize({this->menuButtonWidth, this->menuButtonHeight});
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this->game, SLOT(gameStart()));
	QObject::connect(this->menuButtons.back(), SIGNAL(clicked()), this, SLOT(showGameWindow()));

	QPushButton *backToMenu = new QPushButton{};
	backToMenu->setText("Back to menu");
	this->gameWindow->addMenuButton(backToMenu);
	QObject::connect(backToMenu, SIGNAL(clicked()), this, SLOT(showGameLauncher()));

	return this;
}