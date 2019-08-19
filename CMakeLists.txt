cmake_minimum_required(VERSION 2.8.12)

PROJECT(collabbots-v1.0)
SET(CMAKE_CXX_STANDARD 11)

SET(OpenCV_DIR /home/pranshumalik14/installation/OpenCV-4.1.0/lib/cmake/opencv4)

if(MSVC)
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS})

MACRO(add_example name)
  ADD_EXECUTABLE(${name} ${name}.cpp)
  TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS} )
ENDMACRO()

ADD_EXECUTABLE(collabbots-v1.0 collabbots-v1.0.cpp vision/vision.cpp vision/vision.h)
TARGET_LINK_LIBRARIES(collabbots-v1.0 ${OpenCV_LIBS})