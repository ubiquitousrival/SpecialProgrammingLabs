#pragma once
#include "IFrameSource.hpp"
#include "IFrameDisplay.hpp"

class MockCamera : public IFrameSource {
    cv::Mat frame;
public:
    MockCamera(const std::string& path) {
        frame = cv::imread(path);
        if (frame.empty()) {
            frame = cv::Mat::zeros(480, 640, CV_8UC3); 
        }
    }

    cv::Mat getFrame() override {
        return frame.clone();
    }

    bool isOpened() override {
        return !frame.empty();
    }
};

class MockDisplay : public IFrameDisplay {
public:
    void show(const cv::Mat& frame) override {
    }
};