cmake_minimum_required(VERSION 3.28)
project(vetman2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(vetman2
        AnimalPage.cpp
        AnimalPage.hpp
        AnimalsPage.cpp
        AnimalsPage.hpp
        OwnerPage.cpp
        OwnerPage.hpp
        OwnersPage.cpp
        OwnersPage.hpp
        VaccinationsPage.cpp
        VaccinationsPage.hpp
        App.cpp
        App.hpp
        Canvas.cpp
        Canvas.hpp
        data.cpp
        ListView.cpp
        main.cpp
        OstreamCanvas.cpp
        OstreamCanvas.hpp
        utils.cpp
        utils.hpp
        View.cpp
        View.hpp
        entities.cpp
        entities.hpp
)

