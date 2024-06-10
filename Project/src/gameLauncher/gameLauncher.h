#ifndef GAMELAUNCHER_H
#define GAMELAUNCHER_H

#include <QMainWindow>
#include <QWidget>
#include <string>
#include <functional>

class GameWindow;

class Game;

class GameLauncher : public QMainWindow {
	Q_OBJECT

      protected:
	std::vector<GameWindow *> gameWindows;

      protected:
	GameLauncher *iterateOverGameWindows(std::function<void(GameWindow *)> function);

      public:
	GameLauncher(QWidget *parent = nullptr);

	~GameLauncher();
};

class GameWindow : public QWidget {
	Q_OBJECT

      protected:
	GameLauncher *gameLauncher;

	Game *game;

      public:
	GameWindow(GameLauncher *gameLauncher);

	~GameWindow();
};

class Game : public QWidget {
	Q_OBJECT

      private:
	std::string displayName{"Generic Game"};

      protected:
	GameWindow *gameWindow;

	bool won;

      public:
	Game(GameWindow *gameWindow);

	~Game();

	bool getWon();

	std::string getDisplayName();

      signals:
	void gameEnded();

      public slots:
	void gameEnd();
};

#endif