#include "gameLauncher.h"

GameWindow::~GameWindow() {}

GameWindow::GameWindow(GameLauncher *gameLauncher, QWidget *parent) : QWidget(parent), gameLauncher(gameLauncher) { }