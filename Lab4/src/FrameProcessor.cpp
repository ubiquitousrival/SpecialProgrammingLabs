#include "FrameProcessor.hpp"
#include <iostream>

void FrameProcessor::process(cv::Mat& frame, ProcessMode mode, int brightness, int effectValue, int lagValue, bool faceDetection) {
    
    detector.setDelay(lagValue);
    detector.setFrame(frame);

    if (faceDetection) {
        std::vector<cv::Rect> faces = detector.getResults();
        for (const auto& rect : faces) {
            cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
        }
    }

    if (brightness != 0) {
        frame.convertTo(frame, -1, 1, brightness);
    }

    switch (mode) {
        case ProcessMode::Invert:   applyInvert(frame); break;
        case ProcessMode::Blur:     applyBlur(frame, effectValue); break;
        case ProcessMode::Canny:    applyCanny(frame, effectValue); break;
        case ProcessMode::Sobel:    applySobel(frame); break;
        case ProcessMode::Mirror:   applyMirror(frame); break;
        case ProcessMode::Sepia:    applySepia(frame); break;
        case ProcessMode::Pixelize: applyPixelize(frame, effectValue); break;
        default: break;
    }
}

void FrameProcessor::applyInvert(cv::Mat& frame) {
    cv::bitwise_not(frame, frame);
}

void FrameProcessor::applyBlur(cv::Mat& frame, int value) {
    int ksize = (value % 2 == 0) ? value + 1 : value; 
    if (ksize < 1) ksize = 1;
    cv::GaussianBlur(frame, frame, cv::Size(ksize, ksize), 0);
}

void FrameProcessor::applyCanny(cv::Mat& frame, int value) {
    if (value < 10) value = 10;
    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
    cv::Canny(frame, frame, value, value * 2);
    cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);
}

void FrameProcessor::applySobel(cv::Mat& frame) {
    cv::Mat gray, grad_x, grad_y, abs_grad_x, abs_grad_y;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::Sobel(gray, grad_x, CV_16S, 1, 0, 3);
    cv::Sobel(gray, grad_y, CV_16S, 0, 1, 3);
    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, frame);
    cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);
}

void FrameProcessor::applyMirror(cv::Mat& frame) {
    cv::flip(frame, frame, 1);
}

void FrameProcessor::applySepia(cv::Mat& frame) {
    cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
        0.272, 0.534, 0.131,
        0.349, 0.686, 0.168,
        0.393, 0.769, 0.189);
    cv::transform(frame, frame, kernel);
}

void FrameProcessor::applyPixelize(cv::Mat& frame, int value) {
    if (value < 1) value = 1;
    int h = frame.rows;
    int w = frame.cols;
    cv::resize(frame, frame, cv::Size(w / value, h / value), 0, 0, cv::INTER_LINEAR);
    cv::resize(frame, frame, cv::Size(w, h), 0, 0, cv::INTER_NEAREST);
}