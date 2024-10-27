cmake_minimum_required(VERSION 3.15)
project(RacingGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
)
FetchContent_MakeAvailable(SDL2)

add_executable(racing_game
    src/main.cpp
    src/game.cpp
    src/car.cpp
)

target_link_libraries(racing_game PRIVATE SDL2::SDL2)
