#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
#include <iostream>

int main() {
    CameraProvider camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Error: Camera not found!" << std::endl;
        return -1;
    }

    Display display("Lab 4: Multithreading & Architecture");
    KeyProcessor keys;
    FrameProcessor processor; // Тепер містить детектор всередині

    std::cout << "Press 'F' to toggle Face Detection. '1-8' for effects." << std::endl;

    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) break;

        // Вся логіка інкапсульована в процесорі
        processor.process(
            frame, 
            keys.getMode(), 
            display.brightness, 
            display.effectValue, 
            keys.isFaceDetectionEnabled()
        );
        
        display.show(frame);

        int key = cv::waitKey(10);
        keys.processKey(key);

        if (keys.getShouldExit()) break;
    }
    return 0;
}