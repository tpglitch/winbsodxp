cmake_minimum_required(VERSION 3.15)
project(bsod)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRCS src/*.c)

add_executable(${PROJECT_NAME} ${SRCS})
