#include "FrameProcessor.hpp"
#include <string>

void FrameProcessor::process(cv::Mat& frame, ProcessMode mode, int value) {
    // Вплив повзунка на яскравість через лінійне перетворення
    double alpha = 1.0 + (value - 50) / 50.0;
    frame.convertTo(frame, -1, alpha, 0);

    cv::Mat temp, kernel;
    int pixelSize;

    switch (mode) {
        case ProcessMode::Invert:
            cv::bitwise_not(frame, frame);
            break;
            
        case ProcessMode::Blur:
            // Інтенсивність розмиття залежить від слайдера
            {
                int k = (value / 10) * 2 + 1; 
                cv::GaussianBlur(frame, frame, cv::Size(k, k), 0);
            }
            break;
            
        case ProcessMode::Canny:
            // Детекція граней
            cv::cvtColor(frame, temp, cv::COLOR_BGR2GRAY);
            cv::Canny(temp, temp, 100, 200);
            cv::cvtColor(temp, frame, cv::COLOR_GRAY2BGR); 
            break;
            
        case ProcessMode::Sobel:
            // Оператор Собеля
            cv::cvtColor(frame, temp, cv::COLOR_BGR2GRAY);
            cv::Sobel(temp, temp, CV_8U, 1, 0, 3);
            cv::cvtColor(temp, frame, cv::COLOR_GRAY2BGR);
            break;
            
        case ProcessMode::Mirror:
            cv::flip(frame, frame, 1);
            break;

        case ProcessMode::Sepia:
            // Ефект старої фотографії
            kernel = (cv::Mat_<float>(3, 3) <<
                0.272, 0.534, 0.131,
                0.349, 0.686, 0.168,
                0.393, 0.769, 0.189);
            cv::transform(frame, frame, kernel);
            break;

        case ProcessMode::Pixelize:
            // Ефект пікселізації
            pixelSize = (value / 5) + 1;
            if (pixelSize < 1) pixelSize = 1;
            cv::resize(frame, temp, cv::Size(), 1.0/pixelSize, 1.0/pixelSize, cv::INTER_NEAREST);
            cv::resize(temp, frame, frame.size(), 0, 0, cv::INTER_NEAREST);
            break;
            
        default:
            break;
    }
    
    // Вивід поточного режиму на екран
    cv::putText(frame, "Mode: " + std::to_string((int)mode), cv::Point(10, 30), 
                cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
}
