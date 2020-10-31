cmake_minimum_required (VERSION 3.17)

add_executable (${CMAKE_PROJECT_NAME} "main.cpp")
add_library(${CMAKE_PROJECT_NAME}_lib "")

add_subdirectory(solver)

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

if(MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4 /WX /Za)
    message(STATUS "MSVC")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    message(STATUS "GCC")
endif()

if(NOT CMAKE_BUILD_TYPES MATCHES "Debug")
    if(MSVC)
        set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/GL")
        set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS "/LTCG")
        message(STATUS "MSVC")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -flto -O3)
        message(STATUS "GCC")
    endif()
endif()
