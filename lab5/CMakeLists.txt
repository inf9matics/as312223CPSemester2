project(lab5)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(lab5_exec ${SOURCES})