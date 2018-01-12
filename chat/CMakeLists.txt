cmake_minimum_required(VERSION 3.9)
project(chat)

set(CMAKE_CXX_STANDARD 11)

add_executable(chat client.cpp src/User.h src/Room.h src/Message.h src/User.cpp src/Room.cpp src/Message.cpp server.cpp)