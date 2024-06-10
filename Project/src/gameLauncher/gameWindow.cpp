#include "gameLauncher.h"

GameWindow::~GameWindow() { delete game; }

GameWindow::GameWindow(GameLauncher *gameLauncher) : gameLauncher(gameLauncher) {}