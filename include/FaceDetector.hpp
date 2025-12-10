#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

class FaceDetector {
private:
    cv::dnn::Net net;
    std::thread workerThread;
    std::mutex dataMutex;
    
    std::atomic<bool> isRunning;
    std::atomic<bool> hasNewFrame;
    std::atomic<int> artificialDelay; // Для емуляції навантаження
    std::atomic<double> currentFps;   // Для лічильника
    
    cv::Mat currentFrame;
    std::vector<cv::Rect> detectedFaces;

    void inferenceLoop();

public:
    FaceDetector();
    ~FaceDetector();

    void setFrame(const cv::Mat& frame);
    std::vector<cv::Rect> getResults();
    
    void setDelay(int ms);
    double getFps() const;
};