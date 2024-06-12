set(AUTOMOC ON)

set(SUDOKU_QT_SOURCES sudokuGame.cpp sudokuCellQt.cpp sudokuCellQtValueButton.cpp sudokuCellQtValueDialog.cpp sudokuSubMatrixQt.cpp sudokuMatrixQt.cpp)

qt_add_library(sudokuGame STATIC ${SUDOKU_QT_SOURCES})

target_link_libraries(sudokuGame PUBLIC sudoku sudoku_fileHandling gameLauncher sudoku_backsolver)

target_link_libraries(sudokuGame PRIVATE Qt6::Widgets)
target_include_directories(sudokuGame INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})