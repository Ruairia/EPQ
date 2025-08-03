cmake_minimum_required(VERSION 3.10)
project(EPQ)

set(CMAKE_CXX_STANDARD 17)

# Set path to Raylib and MinGW installation
set(RAYLIB_DIR "C:/raylib")

# Add Raylib headers
include_directories(${RAYLIB_DIR}/raylib/src)

# Add the Raylib static library
link_directories(${RAYLIB_DIR}/raylib/src)

add_executable(raycaster main.cpp
        Vector2D.h
        player.cpp
        player.h
        Map.h
        ray.h)
add_executable(raylib_test raylib_test.cpp raylib_test.h
        raylib_test.cpp
        raylib_test.h)

# Link required libraries
target_link_libraries(raycaster
        raylib
        opengl32
        gdi32
        winmm
        shell32
)
target_link_libraries(raylib_test
        raylib
        opengl32
        gdi32
        winmm
        shell32
)
