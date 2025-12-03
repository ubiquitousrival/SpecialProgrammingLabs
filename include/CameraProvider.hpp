#pragma once
#include <cstddef>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class CameraProvider {
private:
    cv::VideoCapture cap;
public:
    CameraProvider(int deviceId = 0);
    cv::Mat getFrame();
    bool isOpened();
};
