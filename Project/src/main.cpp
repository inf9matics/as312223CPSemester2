#include <iostream>

#include <QApplication>

#include "gameLauncher.h"
#include "sudoku.h"

int main(int argc, char *argv[]) {
    SudokuMatrix sudokuMatrix{9};

    sudokuMatrix.setValueAt({0, 0}, 1);
    sudokuMatrix.setValueAt({0, 1}, 2);
    sudokuMatrix.setValueAt({0, 2}, 3);
    sudokuMatrix.setValueAt({1, 0}, 4);
    sudokuMatrix.setValueAt({1, 1}, 5);
    sudokuMatrix.setValueAt({1, 2}, 6);
    sudokuMatrix.setValueAt({2, 0}, 7);
    sudokuMatrix.setValueAt({2, 1}, 8);
    sudokuMatrix.setValueAt({2, 2}, 9);

    sudokuMatrix.getCellAtPosition({0, 0}).setParityCell(sudokuMatrix.getCellAtPosition({3, 0}));
    sudokuMatrix.setValueAt({3, 0}, 2);

    // QApplication sudokuApp(argc, argv);

    // GameLauncher gameLauncherWindow;

    // gameLauncherWindow.setWindowTitle("Sudoku Game Launcher");

    // gameLauncherWindow.show();

    // return sudokuApp.exec();
    return 0;
}