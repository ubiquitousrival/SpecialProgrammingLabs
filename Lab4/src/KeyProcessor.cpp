#include "KeyProcessor.hpp"
#include <iostream>

KeyProcessor::KeyProcessor() 
    : currentMode(ProcessMode::Normal), shouldExit(false), faceDetectionEnabled(false) {}

void KeyProcessor::processKey(int key) {
    if (key == -1) return;

    if (key == 27 || key == 'q') shouldExit = true;
    
    if (key == 'f' || key == 'F') {
        faceDetectionEnabled = !faceDetectionEnabled;
        std::cout << "Face Detection: " << (faceDetectionEnabled ? "ON" : "OFF") << std::endl;
    }

    switch (key) {
        case '1': currentMode = ProcessMode::Normal; break;
        case '2': currentMode = ProcessMode::Invert; break;
        case '3': currentMode = ProcessMode::Blur; break;
        case '4': currentMode = ProcessMode::Canny; break;
        case '5': currentMode = ProcessMode::Sobel; break;
        case '6': currentMode = ProcessMode::Mirror; break;
        case '7': currentMode = ProcessMode::Sepia; break;
        case '8': currentMode = ProcessMode::Pixelize; break;
    }
}

ProcessMode KeyProcessor::getMode() const { return currentMode; }
bool KeyProcessor::getShouldExit() const { return shouldExit; }
bool KeyProcessor::isFaceDetectionEnabled() const { return faceDetectionEnabled; }