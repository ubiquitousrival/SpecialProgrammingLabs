#pragma once

enum class ProcessMode {
    Normal, Invert, Blur, Canny, Sobel, Mirror, Sepia, Pixelize
};

class KeyProcessor {
private:
    ProcessMode currentMode;
    bool shouldExit;
    bool faceDetectionEnabled; // Новий стан

public:
    KeyProcessor();
    void processKey(int key);
    
    ProcessMode getMode() const;
    bool getShouldExit() const;
    bool isFaceDetectionEnabled() const; // Геттер
};