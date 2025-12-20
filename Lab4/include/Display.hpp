#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "IFrameDisplay.hpp"

class Display : public IFrameDisplay {
public:
    Display(const std::string& title);
    void show(const cv::Mat& frame) override;
    std::string getName();

    int getBrightness() const;
    void setBrightness(int value);

    int getEffectValue() const;
    void setEffectValue(int value);

    int getLagValue() const;
    void setLagValue(int value);

private:
    std::string windowName;
    int brightness;
    int effectValue;
    int lagValue;
};