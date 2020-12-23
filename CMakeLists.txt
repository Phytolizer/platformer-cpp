cmake_minimum_required(VERSION 3.17)
project(platformer)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_executable(platformer ${SOURCES})