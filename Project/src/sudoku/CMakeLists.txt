add_subdirectory(fileHandling)
add_subdirectory(backsolver)

add_library(sudoku STATIC sudoku.cpp)

target_include_directories(sudoku INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})