#include <gtest/gtest.h>
#include <thread>
#include <fstream>
#include <cstdio>
#include "FaceDetector.hpp"
#include "ConfigManager.hpp"
#include "Logger.hpp"
#include "MockClasses.hpp"

void createTestConfig(const std::string& content) {
    std::ofstream out("settings.json");
    out << content;
    out.close();
}

TEST(SystemTest, FaceDetectionLogic) {
    MockCamera mockCam("test_face.jpg"); 
    FaceDetector detector;
    
    cv::Mat frame = mockCam.getFrame();
    ASSERT_FALSE(frame.empty());

    detector.setFrame(frame);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    EXPECT_NO_THROW(detector.getResults());
}

TEST(ConfigTest, ValidConfigLoad) {
    std::string validJson = R"({
        "camera": { "id": 1, "width": 1280, "height": 720 },
        "logging": { "level": "DEBUG" }
    })";
    createTestConfig(validJson);

    ConfigManager::getInstance().loadConfig("settings.json");

    EXPECT_EQ(ConfigManager::getInstance().getCameraId(), 1);
    EXPECT_EQ(ConfigManager::getInstance().getFrameWidth(), 1280);
    EXPECT_EQ(ConfigManager::getInstance().getLogLevel(), "DEBUG");
}

TEST(PatternTest, SingletonUniqueness) {
    Logger& log1 = Logger::getInstance();
    Logger& log2 = Logger::getInstance();
    
    EXPECT_EQ(&log1, &log2);
}

TEST(ConfigTest, MissingFileDefaults) {
    std::remove("settings.json");
    
    ConfigManager::getInstance().loadConfig("settings.json");
    
    EXPECT_EQ(ConfigManager::getInstance().getCameraId(0), 0);
}

TEST(ConfigTest, MalformedJson) {
    createTestConfig("{ \"camera\": { \"id\": 99 "); 
    
    EXPECT_NO_THROW(ConfigManager::getInstance().loadConfig("settings.json"));
    
    EXPECT_EQ(ConfigManager::getInstance().getCameraId(0), 0);
}