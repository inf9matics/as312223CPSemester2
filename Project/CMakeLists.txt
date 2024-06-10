project(sudoku)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(src/gameLauncher)
add_subdirectory(src/sudoku)
add_subdirectory(src/sudokuQt)
add_subdirectory(src/sudokuGame)

set(PROJECT_SOURCES src/main.cpp)

qt_add_executable(project ${PROJECT_SOURCES})
target_link_libraries(project PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(project PRIVATE sudoku sudoku_backsolver)
target_link_libraries(project PRIVATE gameLauncher)
target_link_libraries(project PRIVATE sudokuQt sudokuGame)

target_include_directories(project PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})