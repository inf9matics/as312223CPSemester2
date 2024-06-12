#include "gameLauncher.h"

Game::~Game() {}

Game::Game(GameLauncher *gameLauncher) : gameLauncher(gameLauncher) {}

void Game::gameEnd() {}

void Game::gameStart() {
	this->show();

	emit gameStarted();
}

Game *Game::setGameLauncher(GameLauncher *gameLauncher) {
	this->gameLauncher = gameLauncher;
    this->QWidget::setParent(this->gameLauncher->getGameWindow());

	QObject::connect(this, SIGNAL(gameStarted()), gameLauncher, SLOT(gameStartTime()));

	return this;
}

Game *Game::setSize() { return this; }