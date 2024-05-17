cmake_minimum_required(VERSION 3.28)
project(vetman2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

set(COMMON_FILES
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
        econio.cpp
        econio.hpp
        entities.cpp
        entities.hpp
        utils.cpp
        utils.hpp
)

add_executable(vetman2
        main.cpp
        ${COMMON_FILES}
)

add_executable(test
        test.cpp
        gtest_lite.h
        ${COMMON_FILES}
)
target_compile_definitions(test PUBLIC RUNTEST)