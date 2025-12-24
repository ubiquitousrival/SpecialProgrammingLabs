#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <thread>
#include "ConfigManager.hpp"
#include "FrameProcessor.hpp"
#include "KeyProcessor.hpp"
#include "MockClasses.hpp"

void createConfigFile(const std::string& filename, const std::string& content) {
    std::ofstream out(filename);
    out << content;
    out.close();
}

TEST(ConfigManagerTest, SettersAndGetters) {
    ConfigManager& config = ConfigManager::getInstance();
    
    config.setCameraId(99);
    config.setFrameWidth(1920);
    config.setLogLevel("ERROR");

    EXPECT_EQ(config.getCameraId(), 99);
    EXPECT_EQ(config.getFrameWidth(), 1920);
    EXPECT_EQ(config.getLogLevel(), "ERROR");
}

TEST(ConfigManagerTest, SaveAndLoadCycle) {
    std::string testFile = "test_config_cycle.json";
    ConfigManager& config = ConfigManager::getInstance();

    config.setCameraId(42);
    config.setLogLevel("DEBUG");

    config.saveConfig(testFile);

    config.setCameraId(0);
    
    config.loadConfig(testFile);

    EXPECT_EQ(config.getCameraId(), 42);
    EXPECT_EQ(config.getLogLevel(), "DEBUG");

    std::remove(testFile.c_str());
}

TEST(ConfigManagerTest, MissingFileSafeLoad) {
    ConfigManager::getInstance().loadConfig("non_existent_file.json");
    EXPECT_NO_THROW(ConfigManager::getInstance().getCameraId());
}

TEST(FrameProcessorTest, InvertPixelCheck) {
    FrameProcessor processor;
    cv::Mat frame = cv::Mat::zeros(10, 10, CV_8UC3);
    
    processor.process(frame, ProcessMode::Invert, 0, 0, 0, false);

    cv::Vec3b pixel = frame.at<cv::Vec3b>(5, 5);
    EXPECT_EQ((int)pixel[0], 255); 
    EXPECT_EQ((int)pixel[1], 255); 
    EXPECT_EQ((int)pixel[2], 255); 
}

TEST(KeyProcessorTest, ModeSwitching) {
    KeyProcessor keyProc;
    
    keyProc.processKey('3');
    EXPECT_EQ(keyProc.getMode(), ProcessMode::Blur);

    bool initialState = keyProc.isFaceDetectionEnabled();
    keyProc.processKey('f');
    EXPECT_NE(keyProc.isFaceDetectionEnabled(), initialState);
}

TEST(IntegrationTest, MockCameraReadsFile) {
    MockCamera mockCam("test_face.jpg");
    cv::Mat frame = mockCam.getFrame();
    ASSERT_FALSE(frame.empty()) << "Test image not found or empty!";
}