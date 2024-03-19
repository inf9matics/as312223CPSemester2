project(lab2)

include_directories(inc ../lab1/inc)

file(GLOB SOURCES src/*.cpp)

add_library(lab2_library ${SOURCES})
add_executable(lab2_exec ${SOURCES})

target_link_libraries(lab2_exec lab1_library)