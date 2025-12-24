#pragma once
#include <opencv2/opencv.hpp>

class IFrameDisplay {
public:
    virtual ~IFrameDisplay() = default;
    virtual void show(const cv::Mat& frame) = 0;
};