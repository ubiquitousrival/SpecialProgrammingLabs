#include "KeyProcessor.hpp"

KeyProcessor::KeyProcessor() : currentMode(ProcessMode::Normal), shouldExit(false) {}

void KeyProcessor::processKey(int key) {
    if (key == 27 || key == 'q') { 
        shouldExit = true;
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

ProcessMode KeyProcessor::getMode() const {
    return currentMode;
}

bool KeyProcessor::getShouldExit() const {
    return shouldExit;
}
