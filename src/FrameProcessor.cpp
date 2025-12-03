#include "FrameProcessor.hpp"
#include <string>

void FrameProcessor::process(cv::Mat& frame, ProcessMode mode, int brightnessVal) {
    // 1. Зміна яскравості
    frame.convertTo(frame, -1, 1, brightnessVal - 50);

    cv::Mat gray, temp;

    switch (mode) {
        case ProcessMode::Invert:
            cv::bitwise_not(frame, frame);
            break;

        case ProcessMode::Blur:
            cv::GaussianBlur(frame, frame, cv::Size(15, 15), 0);
            break;

        case ProcessMode::Canny:
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::Canny(gray, temp, 100, 200);
            cv::cvtColor(temp, frame, cv::COLOR_GRAY2BGR); 
            break;

        case ProcessMode::Sobel:
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::Sobel(gray, temp, CV_8U, 1, 0, 3);
            cv::cvtColor(temp, frame, cv::COLOR_GRAY2BGR);
            break;

        case ProcessMode::Mirror:
            cv::flip(frame, frame, 1);
            break;

        default:
            break;
    }

    // Вивід тексту
    cv::putText(frame, "Mode: " + std::to_string((int)mode), cv::Point(10, 30), 
                cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
}
