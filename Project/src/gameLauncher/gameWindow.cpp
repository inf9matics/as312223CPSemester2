#include "gameLauncher.h"

GameWindow::~GameWindow() {}

GameWindow::GameWindow(GameLauncher *gameLauncher, QWidget *parent) : gameLauncher(gameLauncher), QWidget(parent) {}

GameWindow *GameWindow::setGame(Game *game) {
	this->game = game;

	return this;
}

Game *GameWindow::getGame() { return this->game; }

GameWindow *GameWindow::showGame() {
	this->game->show();

	return this;
}