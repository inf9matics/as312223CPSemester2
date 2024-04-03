project(sudoku)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(src/gameLauncher)
add_subdirectory(src/sudoku)

include_directories(src)
file(GLOB SOURCES src/main.cpp)

qt_add_executable(sudoku_qt ${SOURCES})
target_link_libraries(sudoku_qt PRIVATE gameLauncher Qt6::Widgets)
target_link_libraries(sudoku_qt PRIVATE sudoku)