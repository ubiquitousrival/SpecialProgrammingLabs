#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include <iostream>

int main() {
    Logger::getInstance().info("Application started");

    CameraProvider camera(0);
    if (!camera.isOpened()) {
        Logger::getInstance().error("Camera Error: Could not open device 0");
        return -1;
    }
    Logger::getInstance().info("Camera initialized successfully");

    Display display("Lab 4: Advanced Architecture");
    KeyProcessor keys;
    FrameProcessor processor;

    std::cout << "Controls: F (Face), 1-8 (Modes), Sliders" << std::endl;

    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) {
            Logger::getInstance().warn("Received empty frame from camera");
            break;
        }

        processor.process(
            frame,
            keys.getMode(),
            display.brightness,
            display.effectValue,
            display.lagValue,
            keys.isFaceDetectionEnabled()
        );

        display.show(frame);

        int key = cv::waitKey(10);
        keys.processKey(key);

        if (keys.getShouldExit()) {
            Logger::getInstance().info("Exit key pressed. Stopping application...");
            break;
        }
    }
    
    Logger::getInstance().info("Application finished");
    return 0;
}
