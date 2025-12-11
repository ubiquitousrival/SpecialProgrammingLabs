#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
#include <iostream>

int main() {
    CameraProvider camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Camera Error" << std::endl;
        return -1;
    }

    Display display("Lab 4: Advanced Architecture");
    KeyProcessor keys;
    FrameProcessor processor; 

    std::cout << "Controls: F (Face), 1-8 (Modes), Sliders" << std::endl;

    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) break;

        processor.process(
            frame, 
            keys.getMode(), 
            display.brightness, 
            display.effectValue,
            display.lagValue,
            keys.isFaceDetectionEnabled()
        );
        
        display.show(frame);

        int key = cv::waitKey(10);
        keys.processKey(key);

        if (keys.getShouldExit()) break;
    }
    return 0;
}