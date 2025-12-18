#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "ConfigManager.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void setupLogging() {
    std::string levelStr = ConfigManager::getInstance().getLogLevel();
    LogLevel level = LogLevel::INFO;
    
    if (levelStr == "DEBUG") level = LogLevel::DEBUG;
    else if (levelStr == "WARN") level = LogLevel::WARN;
    else if (levelStr == "ERROR") level = LogLevel::ERROR;
    
    Logger::getInstance().setLevel(level);
}

int main() {
    ConfigManager::getInstance().loadConfig("settings.json");
    setupLogging();

    Logger::getInstance().info("Application started");

    int camId = ConfigManager::getInstance().getCameraId(0);
    CameraProvider camera(camId);
    
    if (!camera.isOpened()) {
        Logger::getInstance().error("Camera Error: Could not open device " + std::to_string(camId));
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
            Logger::getInstance().warn("Empty frame received. Waiting for camera...");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
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