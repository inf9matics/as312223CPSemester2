#include "gameLauncher.h"

#include "moc_gameLauncher.cpp"

GameLauncher::~GameLauncher() {
	this->iterateOverGameWindows([](GameWindow *gameWindow) { delete gameWindow; });
}

GameLauncher::GameLauncher(QWidget *parent) : QMainWindow(parent) {}

GameLauncher *GameLauncher::iterateOverGameWindows(std::function<void(GameWindow *)> function) {
	std::vector<GameWindow *>::iterator gameWindowsIterator = this->gameWindows.begin();
	while (gameWindowsIterator != this->gameWindows.end()) {
		function(*gameWindowsIterator);
		gameWindowsIterator++;
	}

	return this;
}