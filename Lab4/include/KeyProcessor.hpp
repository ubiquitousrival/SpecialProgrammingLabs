#pragma once
#include "FrameProcessor.hpp" 
#include <opencv2/opencv.hpp>

class KeyProcessor {
public:
    KeyProcessor();

    void processKey(int key);
    ProcessMode getMode() const;
    bool isFaceDetectionEnabled() const;
    bool getShouldExit() const;

private:
    ProcessMode currentMode;
    bool faceDetectionEnabled;
    bool shouldExit;
};