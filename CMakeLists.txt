cmake_minimum_required(VERSION 3.28)
project(TextBasedRPG C)

set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_mixer include dirs: ${SDL2_MIXER_INCLUDE_DIRS}")
message(STATUS "SDL2_mixer libraries: ${SDL2_MIXER_LIBRARIES}")

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

add_executable(TextBasedRPG main.c
        inventory.h
        inventory.c)

target_link_libraries(TextBasedRPG ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} SDL2 SDL2_mixer)
