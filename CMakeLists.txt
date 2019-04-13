
cmake_minimum_required(VERSION 3.13)

project(lem-in)

set(CMAKE_C_STANDARD 99)

AUX_SOURCE_DIRECTORY(libft LIBFT)
AUX_SOURCE_DIRECTORY(libft/ft_printf FT_PRINTF)
AUX_SOURCE_DIRECTORY(libft/ft_gnl FT_GNL)
AUX_SOURCE_DIRECTORY(libft/vis VIS)
AUX_SOURCE_DIRECTORY(SDL2_primitives SDL2GFX)
AUX_SOURCE_DIRECTORY(flemin FLEMIN)

add_executable(lem-in_clion
        ${LIBFT}
        ${FT_GNL}
        ${FT_PRINTF}
        ${VIS}
        ${FLEMIN}
        ${SDL2GFX})

target_include_directories(lem-in_clion PUBLIC "/Users/dderevyn/.brew/Cellar/sdl_ttf/2.0.11_1/include/SDL/")

target_link_libraries(lem-in_clion "-L /Users/dderevyn/.brew/Cellar/sdl_ttf/2.0.11_1/lib -l SDL_ttf")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_link_libraries(lem-in_clion "-framework SDL2")
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(lem-in_clion "SDL2")
endif()