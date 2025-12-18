cmake_minimum_required(VERSION 3.10)
project(lab4_app)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories(include)

add_executable(lab4_app 
    src/main.cpp 
    src/Logger.cpp
    src/Display.cpp
    src/FaceDetector.cpp
    src/FrameProcessor.cpp
    src/CameraProvider.cpp
    src/KeyProcessor.cpp
    src/ConfigManager.cpp
)

target_link_libraries(lab4_app ${OpenCV_LIBS} Threads::Threads)
