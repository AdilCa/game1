cmake_minimum_required(VERSION 3.27)
project(game1)

set(CMAKE_CXX_STANDARD 20)

link_libraries(libeasyx.a)

include_directories(include src)

add_executable(game1 main.cpp
        include/game.h
        include/utils.h
        src/utils.cpp
        src/game.cpp
        include/game_matrix.h
        src/game_matrix.cpp
        include/game_ui.h
        src/game_ui.cpp)
