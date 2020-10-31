cmake_minimum_required (VERSION 3.17)

set(SOURCES
        cell.hpp
        cell.cpp
        options.hpp
        options.cpp
        region.hpp
        region.cpp
        sudoku.hpp
        sudoku.cpp
    )

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCES})
target_sources(${CMAKE_PROJECT_NAME}_lib PRIVATE ${SOURCES})
