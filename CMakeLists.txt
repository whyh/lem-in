cmake_minimum_required(VERSION 3.13)

project(lemin)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXECUTABLE_SUFFIX _cmake)
set(CMAKE_EXECUTABLE_LEMIN lemin${CMAKE_EXECUTABLE_SUFFIX})

set(LIBS_PATH libs/)
set(INCS_PATH includes/)
set(SRCS_PATH srcs/)

if (${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    set(LIBSV Darwin/)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    set(LIBSV Linux/)
else()
    message( FATAL_ERROR "Your system is not supported.")
endif()

set(LIBFT_PATH      libft/)
set(LIBFT_INCS_PATH ${LIBFT_PATH}${INCS_PATH})

set(SDL2_PATH       ${LIBS_PATH}SDL2/)
set(SDL2_INCS_PATH  ${SDL2_PATH}${INCS_PATH})

set(SDL2_GFX_PATH       ${LIBS_PATH}SDL2_gfx/)
set(SDL2_GFX_INCS_PATH  ${SDL2_GFX_PATH}${INCS_PATH})

set(SDL2_TTF_PATH       ${LIBS_PATH}SDL2_ttf/)
set(SDL2_TTF_INCS_PATH  ${SDL2_TTF_PATH}${INCS_PATH})

AUX_SOURCE_DIRECTORY(${SRCS_PATH} SRCS)
add_executable(${CMAKE_EXECUTABLE_LEMIN} ${SRCS})

target_include_directories(${CMAKE_EXECUTABLE_LEMIN}
        PUBLIC ${INCS_PATH}
        PUBLIC ${LIBFT_INCS_PATH}
        PUBLIC ${SDL2_INCS_PATH}
        PUBLIC ${SDL2_GFX_INCS_PATH}
        PUBLIC ${SDL2_TTF_INCS_PATH})

target_link_directories(${CMAKE_EXECUTABLE_LEMIN}
        PUBLIC ${LIBFT_PATH}
        PUBLIC ${SDL2_PATH}${LIBSV}
        PUBLIC ${SDL2_GFX_PATH}${LIBSV}
        PUBLIC ${SDL2_TTF_PATH}${LIBSV})

target_link_libraries(${CMAKE_EXECUTABLE_LEMIN}
        ft
        SDL2
        SDL2_gfx
        SDL2_ttf)