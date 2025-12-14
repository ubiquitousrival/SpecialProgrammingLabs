cmake_minimum_required(VERSION 3.10)
project(Lab4_CV)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

file(GLOB SOURCES "src/*.cpp")

add_executable(lab4_app ${SOURCES})
target_link_libraries(lab4_app ${OpenCV_LIBS} Threads::Threads)

#file(COPY ${CMAKE_SOURCE_DIR}/deploy.prototxt
#     DESTINATION ${CMAKE_BINARY_DIR})

#file(COPY ${CMAKE_SOURCE_DIR}/res10_300x300_ssd_iter_140000.caffemodel
#    DESTINATION ${CMAKE_BINARY_DIR})
