cmake_minimum_required(VERSION 3.15)
project(F1_Linux)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lib)
include_directories(src)

add_executable(F1_Linux
        lib/fort.c
        lib/fort.h
        lib/fort.hpp
        src/affichage.c
        src/affichage.h
        src/child.c
        src/child.h
        src/curses.c
        src/curses.h
        src/display.c
        src/display.h
        src/files.c
        src/files.h
        src/generated_random_numbers.c
        src/generated_random_numbers.h
        src/main.c
        src/time.c
        src/time.h)
