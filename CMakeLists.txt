cmake_minimum_required(VERSION 3.15)
project(F1_Linux)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lib)
include_directories(src)

set(Sources
        lib/fort.c src/child.c
        src/window.c src/display.c src/files.c
        src/prng.c src/main.c
        src/time.c)

set(Headers
        lib/fort.h lib/fort.hpp
        src/child.h src/window.h src/display.h
        src/files.h src/prng.h src/time.h)

add_executable(F1_Linux ${Sources} ${Headers})
