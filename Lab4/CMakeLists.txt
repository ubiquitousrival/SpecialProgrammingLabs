cmake_minimum_required(VERSION 3.10)
project(lab4_app)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories(include)

add_executable(lab4_app 
    src/main.cpp 
    src/Logger.cpp
    src/ConfigManager.cpp
    src/Display.cpp
    src/FaceDetector.cpp
    src/FrameProcessor.cpp
    src/CameraProvider.cpp
    src/KeyProcessor.cpp
)
target_link_libraries(lab4_app ${OpenCV_LIBS} Threads::Threads)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests 
    tests/test_main.cpp
    src/Logger.cpp
    src/ConfigManager.cpp
    src/FaceDetector.cpp
    src/FrameProcessor.cpp
    src/CameraProvider.cpp
    src/Display.cpp
    src/KeyProcessor.cpp 
)

target_include_directories(run_tests PRIVATE include tests)
target_link_libraries(run_tests GTest::gtest_main ${OpenCV_LIBS} Threads::Threads)

include(GoogleTest)
gtest_discover_tests(run_tests)