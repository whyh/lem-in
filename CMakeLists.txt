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

target_include_directories(lem-in_clion PUBLIC "/SDL/SDL2.framework/Headers")

target_link_libraries(lem-in_clion "-F ./SDL/SDL2.framework -framework SDL2")