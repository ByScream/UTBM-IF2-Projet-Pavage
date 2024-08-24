cmake_minimum_required(VERSION 3.27)
project(Projet_Pavage C)

set(CMAKE_C_STANDARD 99)

add_executable(Projet_Pavage main.c
        affichages.c
        affichages.h
        tuiles.c
        tuiles.h
        initialisations.c
        initialisations.h
        structs.h
        save.c
        save.h
        manager.c
        manager.h
        functions.c
        functions.h)
