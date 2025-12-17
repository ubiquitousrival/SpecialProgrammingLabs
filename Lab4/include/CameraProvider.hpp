#pragma once
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>

class CameraProvider {
private:
    cv::VideoCapture cap;
public:
    CameraProvider(int deviceId = 0);
    cv::Mat getFrame();
    bool isOpened();
};