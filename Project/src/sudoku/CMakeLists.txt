add_subdirectory(fileHandling)
add_subdirectory(backsolver)

set(SUDOKU_SOURCES sudokuCell.cpp sudokuMatrix.cpp sudokuSubMatrix.cpp)

add_library(sudoku SHARED ${SUDOKU_SOURCES})

target_include_directories(sudoku PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})