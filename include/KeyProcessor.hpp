#pragma once

enum class ProcessMode {
    Normal, Invert, Blur, Canny, Sobel, Mirror, Sepia, Pixelize
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