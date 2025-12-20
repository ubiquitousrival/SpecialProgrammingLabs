#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "IFrameDisplay.hpp"

class Display : public IFrameDisplay {
public:
    Display(const std::string& title);
    void show(const cv::Mat& frame) override;
    int brightness;
    int effectValue;
    int lagValue;
private:
    std::string windowName;
};