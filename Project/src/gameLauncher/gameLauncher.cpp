#include "gameLauncher.h"

#include "moc_gameLauncher.cpp"

GameLauncher::~GameLauncher() {
	this->iterateOverMenuButtons([](QPushButton *menuButton) { delete menuButton; });
}

GameLauncher::GameLauncher(QWidget *parent) : QMainWindow(parent), game(new Game{this}), gameWindow(new GameWindow{this}), menuBar(new QWidget{this}) {
	this->menuBar->setLayout(&this->menuButtonsLayout);

	this->prepareButtons();

	this->styleLayout();
}

GameLauncher *GameLauncher::iterateOverMenuButtons(std::function<void(QPushButton *)> function) {
	std::vector<QPushButton *>::iterator menuButtonsIterator = this->menuButtons.begin();
	while (menuButtonsIterator != this->menuButtons.end()) {
		function(*menuButtonsIterator);

		menuButtonsIterator++;
	}

	return this;
}

GameLauncher *GameLauncher::styleLayout() {
	this->menuButtonsLayout.setSpacing(0);
	this->menuButtonsLayout.setContentsMargins({0, 0, 0, 0});

	return this;
}

Game *GameLauncher::getGame() { return this->game; }

GameWindow *GameLauncher::getGameWindow() { return this->gameWindow; }

GameLauncher *GameLauncher::prepareButtons() { return this; }

GameLauncher *GameLauncher::setSize() {
	this->menuBar->setFixedHeight(this->menuButtonHeight * this->menuButtons.size());
	this->menuBar->setFixedWidth(this->menuButtonWidth);
	this->menuBar->setFixedSize(this->menuBar->size() * 1.1);

	this->setFixedSize(this->menuBar->size());

	return this;
}

void GameLauncher::showGameWindow() {
	this->menuBar->hide();

	this->gameWindow->setSize();
	this->gameWindow->showGame();
	this->gameWindow->showMenu();
	this->gameWindow->show();
	this->setFixedSize(this->gameWindow->size());
}

void GameLauncher::showGameLauncher() {
	this->gameWindow->hide();
	this->game->hide();

	this->menuBar->show();
	this->GameLauncher::setSize();
	this->show();
}