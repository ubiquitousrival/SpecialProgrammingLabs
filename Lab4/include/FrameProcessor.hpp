#pragma once
#include <opencv2/opencv.hpp>

enum class ProcessMode {
    None = 0,
    Invert,
    Blur,
    Canny,
    Sobel,
    Mirror,
    Sepia,
    Pixelize
};

class FrameProcessor {
public:
    void process(cv::Mat& frame, ProcessMode mode, int brightness, int effectValue, int lagValue, bool faceDetection);

private:
    void applyInvert(cv::Mat& frame);
    void applyBlur(cv::Mat& frame, int value);
    void applyCanny(cv::Mat& frame, int value);
    void applySobel(cv::Mat& frame);
    void applyMirror(cv::Mat& frame);
    void applySepia(cv::Mat& frame);
    void applyPixelize(cv::Mat& frame, int value);
};