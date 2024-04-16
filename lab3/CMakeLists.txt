project(lab3)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(lab3_exec ${SOURCES})