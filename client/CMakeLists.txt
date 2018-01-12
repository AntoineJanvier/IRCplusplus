cmake_minimum_required(VERSION 3.8)
project(client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES server.cpp src/User.h src/Room.h src/ServerSocket.cpp src/ServerSocket.h src/Socket.h src/Socket.cpp src/SocketException.h)

add_executable(
        client ${SOURCE_FILES}
)