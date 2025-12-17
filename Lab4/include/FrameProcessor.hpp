#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "KeyProcessor.hpp"
#include "FaceDetector.hpp"

class FrameProcessor {
private:
    FaceDetector detector;

public:
    void process(cv::Mat& frame, ProcessMode mode, int brightnessVal, int effectVal, int lagVal, bool isDetectionEnabled);
};