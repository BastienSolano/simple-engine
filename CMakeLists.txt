cmake_minimum_required(VERSION 3.10)

project(simple-engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES src/Bitboard.cpp src/Board.cpp src/main.cpp)

add_executable(simple-engine ${SOURCES})

target_include_directories(simple-engine
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)