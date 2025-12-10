#include "FrameProcessor.hpp"

void FrameProcessor::process(cv::Mat& frame, ProcessMode mode, int brightnessVal, int effectVal) {
    double alpha = 1.0 + (brightnessVal - 50) / 50.0;
    frame.convertTo(frame, -1, alpha, 0);

    cv::Mat temp, kernel, sepia;
    int pixelSize, k;

    switch (mode) {
        case ProcessMode::Invert:
            cv::bitwise_not(frame, frame);
            break;
        case ProcessMode::Blur:
            k = (effectVal / 10) * 2 + 1; 
            cv::GaussianBlur(frame, frame, cv::Size(k, k), 0);
            break;
        case ProcessMode::Canny:
            cv::cvtColor(frame, temp, cv::COLOR_BGR2GRAY);
            cv::Canny(temp, temp, effectVal * 2 + 50, (effectVal * 2 + 50) * 2);
            cv::cvtColor(temp, frame, cv::COLOR_GRAY2BGR); 
            break;
        case ProcessMode::Sobel:
            cv::cvtColor(frame, temp, cv::COLOR_BGR2GRAY);
            cv::Sobel(temp, temp, CV_8U, 1, 0, 3);
            cv::cvtColor(temp, frame, cv::COLOR_GRAY2BGR);
            break;
        case ProcessMode::Mirror:
            cv::flip(frame, frame, 1);
            break;
        case ProcessMode::Sepia:
            kernel = (cv::Mat_<float>(3, 3) <<
                0.272, 0.534, 0.131,
                0.349, 0.686, 0.168,
                0.393, 0.769, 0.189);
            cv::transform(frame, sepia, kernel);
            cv::addWeighted(sepia, effectVal / 100.0, frame, 1.0 - (effectVal / 100.0), 0, frame);
            break;
        case ProcessMode::Pixelize:
            pixelSize = (effectVal / 5) + 1;
            if (pixelSize < 1) pixelSize = 1;
            cv::resize(frame, temp, cv::Size(), 1.0/pixelSize, 1.0/pixelSize, cv::INTER_NEAREST);
            cv::resize(temp, frame, frame.size(), 0, 0, cv::INTER_NEAREST);
            break;
        default: break;
    }
}