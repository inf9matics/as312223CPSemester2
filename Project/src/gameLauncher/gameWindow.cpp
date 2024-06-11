#include "gameLauncher.h"

GameWindow::~GameWindow() { delete this->menuBar; }

GameWindow::GameWindow(GameLauncher *gameLauncher, QWidget *parent) : QWidget(parent), gameLauncher(gameLauncher), menuBar(new QPushButton{this}), menuBarLayout(this) { this->menuBarLayout.addWidget(menuBar); }

GameWindow *GameWindow::setSize() {
	this->setFixedSize(this->gameLauncher->getGame()->size());
	this->setFixedWidth(this->width() + this->menuBar->width());

	return this;
}

void GameWindow::show() {
	this->menuBar->show();

	this->QWidget::show();
}