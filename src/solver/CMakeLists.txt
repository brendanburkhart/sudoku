cmake_minimum_required (VERSION 3.17)

set(SOURCES
        options.hpp
        options.cpp
        region.hpp
        region.cpp
        sudoku.hpp
        sudoku.cpp
        super_region.hpp
        super_region.cpp
    )

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCES})
target_sources(${CMAKE_PROJECT_NAME}_lib PRIVATE ${SOURCES})
