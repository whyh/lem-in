
cmake_minimum_required(VERSION 3.13)

project(lem-in)

set(CMAKE_C_STANDARD 99)

AUX_SOURCE_DIRECTORY(srcs
        SRCS)

add_executable(lem-in_clion
        ${SRCS})

target_include_directories(lem-in_clion
        PUBLIC includes
        PUBLIC libft/includes
        PUBLIC libs/SDL2/includes
        PUBLIC libs/SDL2_gfx/includes
        PUBLIC libs/SDL2_ttf/includes)

target_link_directories(lem-in_clion
        PUBLIC libft/
        PUBLIC libs/SDL2/
        PUBLIC libs/SDL2_gfx/
        PUBLIC libs/SDL2_ttf/)

target_link_libraries(lem-in_clion
        libft.a
        libSDL2-2.0.0.dylib
        libSDL2_gfx-1.0.0.dylib
        libSDL2_ttf-2.0.0.dylib)
