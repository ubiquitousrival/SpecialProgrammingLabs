#pragma once
#include <opencv2/opencv.hpp>

class IFrameSource {
public:
    virtual ~IFrameSource() = default;
    virtual cv::Mat getFrame() = 0;
    virtual bool isOpened() = 0;
};