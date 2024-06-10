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
	std::vector<Game *> availableGames;

	GameWindow *gameWindow;

	friend GameWindow;
	GameLauncher *setGameWindow(GameWindow *gameWindow);

      public:
	GameLauncher(QWidget *parent = nullptr);

	GameWindow *getGameWindow();

	GameLauncher *addGame(Game *game);

	GameLauncher *showGameWindow();

	~GameLauncher();
};

class GameWindow : public QWidget {
	Q_OBJECT

      protected:
	GameLauncher *gameLauncher;

	Game *game;
	friend GameLauncher;
	GameWindow *setGame(Game *game);

      public:
	GameWindow(GameLauncher *gameLauncher, QWidget *parent = nullptr);

	Game *getGame();

	GameWindow *showGame();

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

	bool getWon();

	std::string getDisplayName();

      signals:
	void gameEnded();

      public slots:
	void gameEnd();

	virtual void showGame();
};

#endif