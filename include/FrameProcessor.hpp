#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "KeyProcessor.hpp"
#include "FaceDetector.hpp" // Включаємо детектор сюди

class FrameProcessor {
private:
    FaceDetector detector; // Детектор тепер живе всередині процесора

public:
    // Додаємо прапорець isDetectionEnabled
    void process(cv::Mat& frame, ProcessMode mode, int brightnessVal, int effectVal, bool isDetectionEnabled);
};