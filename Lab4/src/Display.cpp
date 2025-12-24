#include "Display.hpp"

Display::Display(const std::string& title) 
    : windowName(title), brightness(0), effectValue(0), lagValue(1) {
    cv::namedWindow(windowName);
}

void Display::show(const cv::Mat& frame) {
    if (!frame.empty()) {
        cv::imshow(windowName, frame);
    }
}

std::string Display::getName() {
    return windowName;
}

int Display::getBrightness() const {
    return brightness;
}

void Display::setBrightness(int value) {
    brightness = value;
}

int Display::getEffectValue() const {
    return effectValue;
}

void Display::setEffectValue(int value) {
    effectValue = value;
}

int Display::getLagValue() const {
    return lagValue;
}

void Display::setLagValue(int value) {
    if (value < 1) value = 1; 
    lagValue = value;
}