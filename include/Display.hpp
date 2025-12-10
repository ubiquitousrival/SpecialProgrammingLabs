#pragma once
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

class Display {
private:
    std::string windowName;
public:
    int brightness; 
    int effectValue;
    Display(const std::string& name);
    void show(const cv::Mat& frame);
    std::string getName();
};