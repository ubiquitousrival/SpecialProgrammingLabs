#include "CameraProvider.hpp"
#include "KeyProcessor.hpp"
#include "FrameProcessor.hpp"
#include "Display.hpp"
#include "FaceDetector.hpp"
#include <iostream>

int main() {
    CameraProvider camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Camera Error" << std::endl;
        return -1;
    }

    Display display("Lab 4: Multithreading");
    KeyProcessor keys;
    FrameProcessor processor;
    FaceDetector detector;
    
    bool showFaces = true;

    while (true) {
        cv::Mat frame = camera.getFrame();
        if (frame.empty()) break;

        if (showFaces) {
            detector.setFrame(frame);
        }

        processor.process(frame, keys.getMode(), display.brightness, display.effectValue);

        if (showFaces) {
            std::vector<cv::Rect> faces = detector.getResults();
            for (const auto& rect : faces) {
                cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);
                cv::putText(frame, "Face", cv::Point(rect.x, rect.y - 10), 
                            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
            }
        }

        display.show(frame);

        int key = cv::waitKey(10);
        keys.processKey(key);

        if (key == 'f' || key == 'F') {
            showFaces = !showFaces;
        }

        if (keys.getShouldExit()) break;
    }

    return 0;
}