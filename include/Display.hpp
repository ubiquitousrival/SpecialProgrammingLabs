#pragma once
#include <cstddef>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

class Display {
private:
    std::string windowName;
public:
    int brightness; 
    Display(std::string name);
    void show(const cv::Mat& frame);
    std::string getName();
};
