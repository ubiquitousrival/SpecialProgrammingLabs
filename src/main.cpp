#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
#include <iostream>

int main() {
    CameraProvider camera(0);
    if (!camera.isOpened()) {
        std::cout << "Error: Camera not found!" << std::endl;
        return -1;
    }

    Display display("Lab 3 OpenCV");
    KeyProcessor keys;
    FrameProcessor processor;

    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) break;

        // Передача значень обох повзунків у процесор
        processor.process(frame, keys.getMode(), display.brightness, display.effectValue);
        
        display.show(frame);

        int key = cv::waitKey(10);
        keys.processKey(key);

        if (keys.getShouldExit()) break;
    }
    return 0;
}
