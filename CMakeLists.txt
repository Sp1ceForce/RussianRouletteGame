cmake_minimum_required(VERSION 3.21)
project(RussianRoulette)
set(CMAKE_CXX_STANDARD 17)

include_directories(./Players ./Controller ./Helpers)
add_executable(RussianRoulette main.cpp Controller/GameController.cpp Controller/GameController.h Players/Player.cpp Players/Player.h Helpers/ConsoleHelpers.cpp Helpers/ConsoleHelpers.h)
