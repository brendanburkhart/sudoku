cmake_minimum_required(VERSION 3.17)
project(sudoku
    VERSION 0.1.0
    LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CTest)

add_subdirectory(src)
add_subdirectory(test)
