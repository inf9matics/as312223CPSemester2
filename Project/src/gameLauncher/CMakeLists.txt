qt_add_library(gameLauncher STATIC gameLauncher.cpp)

target_link_libraries(gameLauncher PRIVATE Qt6::Widgets)
target_include_directories(gameLauncher INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})