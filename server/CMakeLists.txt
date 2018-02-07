cmake_minimum_required(VERSION 3.8)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES_FILES server.cpp)

add_executable(
        server ${SOURCES_FILES}
)