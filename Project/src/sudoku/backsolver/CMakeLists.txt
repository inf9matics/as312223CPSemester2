set(SUDOKU_BACKSOLVER_SOURCES sudokuBacksolver.cpp sudokuMatrixMasked.cpp)

add_library(sudoku_backsolver SHARED ${SUDOKU_BACKSOLVER_SOURCES})

target_include_directories(sudoku_backsolver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(sudoku_backsolver sudoku)
target_include_directories(sudoku_backsolver PRIVATE sudoku)