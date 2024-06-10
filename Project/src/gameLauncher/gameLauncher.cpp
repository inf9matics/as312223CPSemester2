#include "gameLauncher.h"

#include "moc_gameLauncher.cpp"

GameLauncher::~GameLauncher() {}

GameLauncher::GameLauncher(QWidget *parent) : QMainWindow(parent) { this->gameWindow = new GameWindow{this, this->parentWidget()}; }

GameLauncher *GameLauncher::showGameWindow() {
	this->gameWindow->showGame()->show();

	return this;
}

GameWindow *GameLauncher::getGameWindow() { return this->gameWindow; }

GameLauncher *GameLauncher::addGame(Game *game) {
	this->availableGames.push_back(game);

	return this;
}