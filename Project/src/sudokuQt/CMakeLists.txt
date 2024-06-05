set(AUTOMOC ON)

set(SUDOKU_QT_SOURCES sudokuCellQt.cpp sudokuCellQtValueDialog.cpp sudokuMatrixQt.cpp)

qt_add_library(sudokuQt STATIC ${SUDOKU_QT_SOURCES})

target_link_libraries(sudokuQt PRIVATE sudoku)

target_link_libraries(sudokuQt PRIVATE Qt6::Widgets)
target_include_directories(sudokuQt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})