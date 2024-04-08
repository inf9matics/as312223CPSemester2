#ifndef GAMELAUNCHER_H
#define GAMELAUNCHER_H

#include <QMainWindow>

class GameLauncher : public QMainWindow {
	Q_OBJECT

      public:
	GameLauncher(QWidget *parent = nullptr);

	~GameLauncher();
};

#endif