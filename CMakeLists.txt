cmake_minimum_required(VERSION 3.14)
project(F1-Linux)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)
include_directories(src)
include_directories(img)


add_executable(F1-Linux

        img/logo.png img/output.gif img/how-to-run-prog.gif
        lib/fort.c lib/fort.h lib/fort.hpp lib/libfort.pc.in
        src/affichage.c src/child.c src/curses.h src/curses.c src/main.c src/child.h
        src/affichage.h src/generated_random_numbers.c src/generated_random_numbers.h
        src/display.c src/display.h src/time.c src/time.h src/files.c src/files.h src/files.c src/files.h)




