#include "KeyProcessor.hpp"
#include "Logger.hpp"
#include <iostream>
#include <string>
#include <map>

KeyProcessor::KeyProcessor() 
    : currentMode(ProcessMode::None), 
      faceDetectionEnabled(false), 
      shouldExit(false) {}

ProcessMode KeyProcessor::getMode() const {
    return currentMode;
}

bool KeyProcessor::isFaceDetectionEnabled() const {
    return faceDetectionEnabled;
}

bool KeyProcessor::getShouldExit() const {
    return shouldExit;
}

void KeyProcessor::processKey(int key) {
    if (key == -1) return;

    char keyChar = static_cast<char>(key);
    Logger::getInstance().debug("Key pressed: '" + std::string(1, keyChar) + "' (code: " + std::to_string(key) + ")");

    if (key == 27 || key == 'q') {
        shouldExit = true;
    }

    if (key == 'f' || key == 'F') {
        faceDetectionEnabled = !faceDetectionEnabled;
        std::string status = faceDetectionEnabled ? "ON" : "OFF";
        Logger::getInstance().info("Face Detection toggled: " + status);
    }

    static std::map<int, std::string> modeNames = {
        {'1', "None"}, {'2', "Invert"}, {'3', "Blur"},
        {'4', "Canny"}, {'5', "Sobel"}, {'6', "Mirror"},
        {'7', "Sepia"}, {'8', "Pixelize"}
    };

    if (key >= '1' && key <= '8') {
        currentMode = static_cast<ProcessMode>(key - '1');
        
        std::string modeName = modeNames.count(key) ? modeNames[key] : "Unknown";
        Logger::getInstance().info("Switched to mode: " + modeName);
    } 
    
    else if (key == '=' || key == '+') {
    } 
    else if (key == '-' || key == '_') {
    }
}