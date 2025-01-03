cmake_minimum_required(VERSION 3.26)
project(debug C)

set(CMAKE_C_STANDARD 11)

add_executable(debug main.c
        auto_kezel.c
        falj_kezel.c
        fugveny.c
        lejar.c
        szerviz_kezel.c
        ugyfel_kezel.c
        econio.c
)
