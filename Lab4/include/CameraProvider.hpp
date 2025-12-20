#pragma once
#include <opencv2/opencv.hpp>
#include "IFrameSource.hpp"

class CameraProvider : public IFrameSource {
private:
    cv::VideoCapture cap;
public:
    CameraProvider(int deviceId, int width, int height);
    
    cv::Mat getFrame() override;
    bool isOpened() override;
};