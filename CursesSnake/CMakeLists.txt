cmake_minimum_required(VERSION 3.5.1)
project(code)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -O3 -Wall -lncurses")

add_executable(fSnake main.cpp Game.cpp Player.cpp SnakePlayer.cpp Food.cpp utils.cpp)
target_link_libraries(fSnake -lncurses)

add_custom_target(main COMMAND fSnake DEPENDS fSnake)