cmake_minimum_required(VERSION 3.10)
project(Lab3_OpenCV)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} include)

file(GLOB SOURCES "src/*.cpp")

add_executable(lab3_app ${SOURCES})
target_link_libraries(lab3_app ${OpenCV_LIBS})
