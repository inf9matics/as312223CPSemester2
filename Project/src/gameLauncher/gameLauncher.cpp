#include "gameLauncher.h"

#include "moc_gameLauncher.cpp"

GameLauncher::~GameLauncher() {
	this->iterateOverMenuButtons([](QPushButton *menuButton) { delete menuButton; });
}

GameLauncher::GameLauncher(Game *game, QWidget *parent) : QMainWindow(parent), game(game), gameWindow(new GameWindow{this, parent}), menuButtonsLayout(this) {
	this->game->setGameWindow(this->gameWindow);
	this->gameWindow->setFixedSize(this->game->size());
}

GameLauncher *GameLauncher::iterateOverMenuButtons(std::function<void(QPushButton *)> function) {
	std::vector<QPushButton *>::iterator menuButtonsIterator = this->menuButtons.begin();
	while (menuButtonsIterator != this->menuButtons.end()) {
		function(*menuButtonsIterator);

		menuButtonsIterator++;
	}

	return this;
}

Game *GameLauncher::getGame() { return this->game; }

GameWindow *GameLauncher::getGameWindow() { return this->gameWindow; }