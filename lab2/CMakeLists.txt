project(lab2)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(lab2_exec ${SOURCES})