project(sudoku)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(src/gameLauncher)
add_subdirectory(src/sudoku)

file(GLOB SOURCES src/main.cpp)

qt_add_executable(sudoku_qt ${SOURCES})
target_link_libraries(sudoku_qt PRIVATE gameLauncher Qt6::Widgets)

target_link_libraries(sudoku_qt PRIVATE sudoku sudoku_backsolver)
target_include_directories(sudoku_qt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(sudoku_qt INTERFACE sudoku sudoku_backsolver)