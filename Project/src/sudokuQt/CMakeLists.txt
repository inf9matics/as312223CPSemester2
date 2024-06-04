set(AUTOMOC ON)

qt_add_library(sudokuQt STATIC sudokuQt.cpp)

target_link_libraries(sudokuQt PRIVATE sudoku)

target_link_libraries(sudokuQt PRIVATE Qt6::Widgets)
target_include_directories(sudokuQt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})