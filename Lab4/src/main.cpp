#include <iostream>
#include <opencv2/opencv.hpp>
#include "Logger.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Logger.hpp"
#include "ConfigManager.hpp"
#include "CameraProvider.hpp"
#include "Display.hpp"
#include "FrameProcessor.hpp"
#include "KeyProcessor.hpp"

int main() {
    ConfigManager& config = ConfigManager::getInstance();
    config.loadConfig("settings.json");

    std::string levelStr = config.getLogLevel();
    LogLevel level = LogLevel::INFO; 

    if (levelStr == "DEBUG") level = LogLevel::DEBUG;
    else if (levelStr == "ERROR") level = LogLevel::ERROR;
    else if (levelStr == "WARN" || levelStr == "WARNING") level = LogLevel::WARNING;
    
    Logger::getInstance().setLevel(level);
    
    Logger::getInstance().info("Application started");

    CameraProvider camera(config.getCameraId());
    if (!camera.isOpened()) {
        Logger::getInstance().error("Failed to open camera!");
        return -1;
    }

    Display display("Lab 4: Final System");
    FrameProcessor processor;
    KeyProcessor keyProcessor;

    Logger::getInstance().info("Entering main loop");

    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) {
            Logger::getInstance().warn("Empty frame received");
            continue;
        }

        int key = cv::waitKey(1);
        keyProcessor.processKey(key);

        if (keyProcessor.getShouldExit()) {
            Logger::getInstance().info("Exit signal received");
            break;
        }

        processor.process(
            frame, 
            keyProcessor.getMode(), 
            display.getBrightness(),  
            display.getEffectValue(), 
            display.getLagValue(),    
            keyProcessor.isFaceDetectionEnabled()
        );

        display.show(frame);
    }

    Logger::getInstance().info("Application finished");
    return 0;
}