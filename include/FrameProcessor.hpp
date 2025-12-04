#pragma once
#include <cstddef>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "KeyProcessor.hpp"

class FrameProcessor {
public:
    void process(cv::Mat& frame, ProcessMode mode, int value);
};
