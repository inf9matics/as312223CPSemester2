set(AUTOMOC ON)

set(SUDOKU_QT_SOURCES sudokuQt.cpp sudokuCellQt.cpp sudokuCellQtValueButton.cpp sudokuCellQtValueDialog.cpp sudokuSubMatrixQt.cpp sudokuMatrixQt.cpp)

qt_add_library(sudokuQt STATIC ${SUDOKU_QT_SOURCES})

target_link_libraries(sudokuQt PUBLIC sudoku)

target_link_libraries(sudokuQt PRIVATE Qt6::Widgets)
target_include_directories(sudokuQt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})