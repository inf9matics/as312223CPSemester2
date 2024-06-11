#ifndef GAMELAUNCHER_H
#define GAMELAUNCHER_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
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

	QWidget *menuBar;
	std::vector<QPushButton *> menuButtons;
	QVBoxLayout menuButtonsLayout;
	Qt::Alignment menuButtonAlignment{Qt::AlignCenter};
	int menuButtonWidth{90};
	int menuButtonHeight{30};

	virtual GameLauncher *prepareButtons();
	GameLauncher *setSize();

	GameLauncher *styleLayout();

      public:
	GameLauncher(QWidget *parent = nullptr);

	GameWindow *getGameWindow();
	Game *getGame();

	~GameLauncher();

      public slots:
	void showGameWindow();

	void showGameLauncher();
};

class GameWindow : public QWidget {
	Q_OBJECT

      protected:
	GameWindow *iterateOverMenuButtons(std::function<void(QPushButton *)> function);

      protected:
	GameLauncher *gameLauncher;

	QWidget *menuBar;
	std::vector<QPushButton *> menuButtons;
	QHBoxLayout menuBarLayout;
	Qt::Alignment menuButtonAlignment{Qt::AlignCenter};
	int menuButtonWidth{90};
	int menuButtonHeight{30};

	QVBoxLayout gameWindowLayout;

	GameWindow *prepareButtons();

	friend GameLauncher;
	GameWindow *setSize();

      public:
	GameWindow(GameLauncher *gameLauncher);

	GameWindow *styleLayout();

	GameWindow *addMenuButton(QPushButton *menuButton);

	~GameWindow();

	void show();

      public slots:
	void showGame();

	void showMenu();
	void hideMenu();
};

class Game : public QWidget {
	Q_OBJECT

      protected:
	std::string displayName{"Generic Game"};

      protected:
	GameLauncher *gameLauncher;

	bool won;

      public:
	Game(GameLauncher *gameLauncher = nullptr);

	~Game();

	Game *setGameLauncher(GameLauncher *gameLauncher);

	bool getWon();

	std::string getDisplayName();

	Game *setSize();

      signals:
	void gameEnded();

	void gameStarted();

      public slots:
	void gameEnd();

	void gameStart();
};

#endif