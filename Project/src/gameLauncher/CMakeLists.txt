set(AUTOMOC ON)

set(GAMELAUNCHER_SOURCES game.cpp gameLauncher.cpp gameWindow.cpp)

qt_add_library(gameLauncher SHARED ${GAMELAUNCHER_SOURCES})

target_link_libraries(gameLauncher PRIVATE Qt6::Widgets)
target_include_directories(gameLauncher INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})