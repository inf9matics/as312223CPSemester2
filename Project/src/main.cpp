#include <iostream>

#include <QApplication>

#include "gameLauncher.h"
#include "sudoku.h"

int main(int argc, char *argv[]) {
    SudokuMatrix sudokuMatrix{9};

    sudokuMatrix.setValueAt(std::pair<int, int>{0, 3}, 7);
    sudokuMatrix.setValueAt(std::pair<int, int>{0, 4}, 7);

    // QApplication sudokuApp(argc, argv);

    // GameLauncher gameLauncherWindow;

    // gameLauncherWindow.setWindowTitle("Sudoku Game Launcher");

    // gameLauncherWindow.show();

    // return sudokuApp.exec();
    return 0;
}