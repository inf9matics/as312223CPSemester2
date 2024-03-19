project(lab1)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(lab1_exec ${SOURCES})