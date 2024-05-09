cmake_minimum_required(VERSION 3.28)
project(vetman2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

add_executable(vetman2
        AnimalPage.cpp
        AnimalPage.hpp
        AnimalsPage.cpp
        AnimalsPage.hpp
        App.cpp
        App.hpp
        Canvas.cpp
        Canvas.hpp
        ListView.cpp
        OstreamCanvas.cpp
        OstreamCanvas.hpp
        OwnerPage.cpp
        OwnerPage.hpp
        OwnersPage.cpp
        OwnersPage.hpp
        VaccinationsPage.cpp
        VaccinationsPage.hpp
        View.cpp
        View.hpp
        data.cpp
        econio.c
        econio.h
        entities.cpp
        entities.hpp
        main.cpp
        utils.cpp
        utils.hpp
)

