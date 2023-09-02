cmake_minimum_required(VERSION 3.25)
project(DesignPatterns)

set(CMAKE_CXX_STANDARD 17)

add_executable(DesignPatterns main.cpp src/adapter/Adapter.cpp src/bridge/Bridge.cpp src/command/Command.cpp)
