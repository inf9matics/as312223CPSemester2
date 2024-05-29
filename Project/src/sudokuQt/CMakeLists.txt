set(SUDOKU_QT_SOURCES sudokuQt.cpp)

add_library(sudokuQt STATIC ${SUDOKU_QT_SOURCES})

target_link_libraries(sudokuQt PRIVATE Qt6::Widgets)
target_link_libraries(sudokuQt PRIVATE sudoku)

target_include_directories(sudokuQt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})