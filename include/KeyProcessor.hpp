#pragma once
#include <opencv2/core.hpp>

enum class ProcessMode {
    Normal,
    Invert,
    Blur,
    Canny,
    Sobel,
    Mirror
};

class KeyProcessor {
private:
    ProcessMode currentMode;
    bool shouldExit;
public:
    KeyProcessor();
    void processKey(int key);
    ProcessMode getMode() const;
    bool getShouldExit() const;
};
