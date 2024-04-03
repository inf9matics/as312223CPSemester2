project(lab2)

include_directories(inc ../lab1/inc)

file(GLOB SOURCES src/*.cpp)

add_executable(lab2_exec ${SOURCES})