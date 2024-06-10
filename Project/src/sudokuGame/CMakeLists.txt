set(AUTOMOC ON)

set(SUDOKU_GAME_SOURCES sudokuGame.cpp)

qt_add_library(sudokuGame SHARED ${SUDOKU_GAME_SOURCES})

target_link_libraries(sudokuGame PUBLIC Qt6::Widgets)
target_link_libraries(sudokuGame PRIVATE sudokuQt gameLauncher)

target_include_directories(sudokuGame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(sudokuGame PRIVATE sudokuQt gameLauncher)