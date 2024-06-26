#include "gameLauncher.h"

GameWindow::~GameWindow() {
	this->iterateOverMenuButtons([](QPushButton *menuButton) { delete menuButton; });
}

GameWindow::GameWindow(GameLauncher *gameLauncher) : QWidget(gameLauncher), gameLauncher(gameLauncher), gameWindowLayout(this) {
	this->menuBar = new QWidget{this};
	this->menuBar->setLayout(&this->menuBarLayout);

	this->menuBarLayout.addWidget(menuBar);
}

GameWindow *GameWindow::setSize() {
	this->menuBar->setFixedSize({this->gameLauncher->getGame()->width(), this->menuButtonHeight});

	this->setFixedSize(this->gameLauncher->getGame()->size());
	this->setFixedHeight(this->height() + this->menuButtonHeight);

	return this;
}

void GameWindow::show() {
	this->menuBar->show();

	this->QWidget::show();
}

GameWindow *GameWindow::iterateOverMenuButtons(std::function<void(QPushButton *)> function) {
	std::vector<QPushButton *>::iterator menuButtonsIterator = this->menuButtons.begin();
	while (menuButtonsIterator != this->menuButtons.end()) {
		function(*menuButtonsIterator);

		menuButtonsIterator++;
	}

	return this;
}

GameWindow *GameWindow::styleLayout() {
	this->menuBarLayout.setSpacing(0);
	this->menuBarLayout.setContentsMargins({0, 0, 0, 0});

	this->gameWindowLayout.setSpacing(0);
	this->gameWindowLayout.setContentsMargins({0, 0, 0, 0});

	this->gameWindowLayout.addWidget(this->menuBar);
	this->gameWindowLayout.addWidget(this->gameLauncher->getGame());

	return this;
}

GameWindow *GameWindow::addMenuButton(QPushButton *menuButton) {
	menuButton->setParent(this);
	this->menuButtons.push_back(menuButton);
	menuButton->setFixedHeight(this->menuButtonHeight);

	return this;
}

void GameWindow::showMenu() {
	this->iterateOverMenuButtons([](QPushButton *menuButton) { menuButton->show(); });
	this->menuBar->show();
}

void GameWindow::hideMenu() {
	this->iterateOverMenuButtons([](QPushButton *menuButton) { menuButton->hide(); });
	this->menuBar->hide();
}

void GameWindow::showGame() { this->gameLauncher->getGame()->show(); }

QPushButton *GameWindow::getMenuButtonsBack() { return this->menuButtons.back(); }

GameWindow *GameWindow::generateMenuButton(std::string label) {
	this->menuButtons.push_back(new QPushButton(this->menuBar));
	this->menuButtons.back()->setFixedSize({(this->menuButtonWidthPerLetter * (int)label.size()), this->menuButtonHeight});
	this->menuBarLayout.addWidget(this->menuButtons.back(), 0, this->menuButtonAlignment);
	this->menuButtons.back()->setText(QString::fromStdString(label));

	return this;
}

GameWindow *GameWindow::addFinalStretch() {
	this->menuBarLayout.addStretch();

	return this;
}