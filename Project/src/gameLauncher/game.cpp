#include "gameLauncher.h"

Game::~Game() {}

Game::Game() {}

void Game::gameEnd() {}

void Game::gameStart() {
	this->gameWindow->show();

	this->show();

	emit gameStarted();
}

Game *Game::setGameWindow(GameWindow *gameWindow) {
    this->QWidget::setParent(gameWindow);
	this->gameWindow = gameWindow;
	return this;
}