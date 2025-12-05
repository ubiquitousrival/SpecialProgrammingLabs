#pragma once
#include <cstddef>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "KeyProcessor.hpp"

class FrameProcessor {
public:
    // Метод приймає два значення для повзунків
    void process(cv::Mat& frame, ProcessMode mode, int brightnessVal, int effectVal);
};
