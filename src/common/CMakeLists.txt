cmake_minimum_required (VERSION 3.17)

set(SOURCES
        sudoku.hpp
        sudoku.cpp
    )

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCES})
target_sources(${CMAKE_PROJECT_NAME}_lib PRIVATE ${SOURCES})
