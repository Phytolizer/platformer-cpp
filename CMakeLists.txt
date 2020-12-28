cmake_minimum_required(VERSION 3.17)
project(platformer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")
add_executable(platformer ${SOURCES} src/level_file_token.cpp src/level_file_token.hpp)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_image SDL2::SDL2_gfx fmt::fmt)
