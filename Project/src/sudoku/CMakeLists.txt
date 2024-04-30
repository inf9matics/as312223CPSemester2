add_library(sudoku STATIC sudoku.cpp)

target_include_directories(sudoku INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(fileHandling)