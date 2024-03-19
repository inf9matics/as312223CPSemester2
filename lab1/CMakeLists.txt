project(lab1)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_library(song_library ${SOURCES})