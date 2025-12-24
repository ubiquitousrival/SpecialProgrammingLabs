#include "CameraProvider.hpp"

CameraProvider::CameraProvider(int deviceId, int width, int height) {
    cap.open(deviceId);
    
    if (cap.isOpened()) {
        cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    }
}

cv::Mat CameraProvider::getFrame() {
    cv::Mat frame;
    if (cap.isOpened()) {
        cap >> frame;
    }
    return frame;
}

bool CameraProvider::isOpened() {
    return cap.isOpened();
}