#include "Display.hpp"

Display::Display(const std::string& name) 
    : windowName(name), brightness(50), effectValue(0), lagValue(0) {
    cv::namedWindow(windowName);
    cv::createTrackbar("Brightness", windowName, &brightness, 100);
    cv::createTrackbar("Effect", windowName, &effectValue, 100);
    cv::createTrackbar("Lag (ms)", windowName, &lagValue, 1000);
}

void Display::show(const cv::Mat& frame) {
    if (!frame.empty()) {
        cv::imshow(windowName, frame);
    }
}

std::string Display::getName() {
    return windowName;
}