#include "gameLauncher.h"

Game::~Game() {}

Game::Game(GameLauncher *gameLauncher) : gameLauncher(gameLauncher) { QObject::connect(this, SIGNAL(gameEnded()), this, SLOT(spawnEndPopup)); }

void Game::gameEnd() {
	this->gameEndTime();
	emit gameEnded();
}

void Game::gameStart() {
	this->show();

	this->gameStartTime();

	emit gameStarted();
}

Game *Game::setGameLauncher(GameLauncher *gameLauncher) {
	this->gameLauncher = gameLauncher;
	this->QWidget::setParent(this->gameLauncher->getGameWindow());

	QObject::connect(this, SIGNAL(gameStarted()), gameLauncher, SLOT(gameStartTime()));

	return this;
}

Game *Game::setSize() { return this; }

void Game::spawnEndPopup() {
	this->endPopupLabel->setWindowFlags(Qt::Popup);
	this->endPopupLabel = new QLabel{this->endPopup};

	std::string resultTime{std::to_string(std::chrono::duration_cast<std::chrono::seconds>(this->gameDuration).count())};
	this->endPopupLabel->setText(QString::fromStdString("You've completed the board after " + resultTime + " seconds"));

	this->endPopup->move(this->geometry().center());
	this->endPopup->show();
}

void Game::gameStartTime() { this->gameStartTimePoint = std::chrono::steady_clock::now(); }

void Game::gameEndTime() {
	this->gameEndTimePoint = std::chrono::steady_clock::now();

	this->gameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(this->gameEndTimePoint - this->gameStartTimePoint);
}