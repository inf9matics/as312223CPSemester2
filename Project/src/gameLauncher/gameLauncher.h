#ifndef GAMELAUNCHER_H
#define GAMELAUNCHER_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>
#include <string>

class GameWindow;

class Game;

class GameLauncher : public QMainWindow {
	Q_OBJECT

      protected:
	GameLauncher *iterateOverMenuButtons(std::function<void(QPushButton *)> function);

      protected:
	GameWindow *gameWindow;
	Game *game;

	std::vector<QPushButton *> menuButtons;
	QVBoxLayout menuButtonsLayout;

	GameLauncher *prepareButtons();

      public:
	GameLauncher(Game *game, QWidget *parent = nullptr);

	GameWindow *getGameWindow();
	Game *getGame();

	~GameLauncher();
};

class GameWindow : public QWidget {
	Q_OBJECT

      protected:
	GameLauncher *gameLauncher;

      public:
	GameWindow(GameLauncher *gameLauncher, QWidget *parent = nullptr);

	~GameWindow();
};

class Game : public QWidget {
	Q_OBJECT

      protected:
	std::string displayName{"Generic Game"};

      protected:
	GameWindow *gameWindow;

	bool won;

      public:
	Game();

	~Game();

	Game *setGameWindow(GameWindow *gameWindow);

	bool getWon();

	std::string getDisplayName();

      signals:
	void gameEnded();

	void gameStarted();

      public slots:
	void gameEnd();

	void gameStart();
};

#endif