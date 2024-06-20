cmake_minimum_required(VERSION 3.26)
project(codecrafters_shell_c C)

set(CMAKE_C_STANDARD 11)

add_executable(codecrafters_shell_c
        app/main.c
        app/commands.h
        app/commands.c
        app/utils.h
        app/utils.c)
