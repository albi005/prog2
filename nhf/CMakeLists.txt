cmake_minimum_required(VERSION 3.28)
project(vetman2)

set(CMAKE_CXX_STANDARD 17)

add_executable(vetman2
        appview.cpp
        appview.hpp
        canvas.cpp
        canvas.hpp
        data.cpp
        listview.cpp
        main.cpp
        ostream_canvas.cpp
        ostream_canvas.hpp
        utils.cpp
        utils.hpp
        view.cpp
        view.hpp
)

