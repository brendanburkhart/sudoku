cmake_minimum_required (VERSION 3.17)

set(SOURCES
        grid_detector.hpp
        grid_detector.cpp
        ocr.hpp
        ocr.cpp
        vision.hpp
        vision.cpp
        quad.hpp
        quad.cpp
    )

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
find_package(Tesseract REQUIRED)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Tesseract_INCLUDE_DIRS})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${Tesseract_LIBRARIES})
 
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCES})
