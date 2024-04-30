project(lab4)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(lab4_exec ${SOURCES})