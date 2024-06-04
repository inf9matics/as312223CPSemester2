project(sudoku)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(src/gameLauncher)
add_subdirectory(src/sudoku)
add_subdirectory(src/sudokuQt)

file(GLOB SOURCES src/main.cpp)

qt_add_executable(sudokuGame ${SOURCES})
target_link_libraries(sudokuGame PRIVATE gameLauncher Qt6::Core Qt6::Widgets)
target_link_libraries(sudokuGame PRIVATE sudoku sudoku_backsolver)
target_link_libraries(sudokuGame PRIVATE sudokuQt)

target_include_directories(sudokuGame INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(sudokuGame INTERFACE sudoku sudoku_backsolver)