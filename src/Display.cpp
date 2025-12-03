#include "Display.hpp"

Display::Display(std::string name) : windowName(name), brightness(50) {
    cv::namedWindow(windowName);
    cv::createTrackbar("Brightness", windowName, &brightness, 100);
}

void Display::show(const cv::Mat& frame) {
    if (!frame.empty()) {
        cv::imshow(windowName, frame);
    }
}

std::string Display::getName() {
    return windowName;
}
