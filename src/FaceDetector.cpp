#include "FaceDetector.hpp"
#include <iostream>
#include <chrono>

FaceDetector::FaceDetector() : isRunning(true), hasNewFrame(false) {
    try {
        net = cv::dnn::readNetFromCaffe("deploy.prototxt", "res10_300x300_ssd_iter_140000.caffemodel");
        workerThread = std::thread(&FaceDetector::inferenceLoop, this);
    } catch (const cv::Exception& e) {
        std::cerr << "Detector Error: " << e.what() << std::endl;
        isRunning = false;
    }
}

FaceDetector::~FaceDetector() {
    isRunning = false;
    if (workerThread.joinable()) {
        workerThread.join();
    }
}

void FaceDetector::setFrame(const cv::Mat& frame) {
    if (frame.empty()) return;
    std::lock_guard<std::mutex> lock(dataMutex);
    frame.copyTo(currentFrame);
    hasNewFrame = true;
}

std::vector<cv::Rect> FaceDetector::getResults() {
    std::lock_guard<std::mutex> lock(dataMutex);
    return detectedFaces;
}

void FaceDetector::inferenceLoop() {
    cv::Mat processFrame;
    
    while (isRunning) {
        bool shouldProcess = false;

        {
            std::lock_guard<std::mutex> lock(dataMutex);
            if (hasNewFrame && !currentFrame.empty()) {
                currentFrame.copyTo(processFrame);
                hasNewFrame = false;
                shouldProcess = true;
            }
        }

        if (shouldProcess) {
            // Штучне навантаження (500мс), щоб показати, що інтерфейс не лагає
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            cv::Mat blob = cv::dnn::blobFromImage(processFrame, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0));
            net.setInput(blob);
            cv::Mat detections = net.forward();

            std::vector<cv::Rect> newFaces;
            cv::Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());

            for (int i = 0; i < detectionMat.rows; i++) {
                float confidence = detectionMat.at<float>(i, 2);
                if (confidence > 0.5) {
                    int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * processFrame.cols);
                    int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * processFrame.rows);
                    int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * processFrame.cols);
                    int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * processFrame.rows);
                    newFaces.emplace_back(cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2)));
                }
            }

            {
                std::lock_guard<std::mutex> lock(dataMutex);
                detectedFaces = newFaces;
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}