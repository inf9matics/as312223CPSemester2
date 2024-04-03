project(sudoku)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(sudoku_exec ${SOURCES})