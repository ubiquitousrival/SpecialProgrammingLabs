#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Помилка: Не вдалося відкрити веб-камеру" << endl;
        return -1;
    }

    cout << "Камера успішно запущена!" << endl;
    cout << "Натисніть 'ESC', щоб вийти з програми." << endl;

    while (true) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cout << "Помилка: Отримано порожній кадр" << endl;
            break;
        }

        Point center(frame.cols / 2, frame.rows / 2);
        circle(frame, center, 50, Scalar(0, 255, 0), 3);
        putText(frame, "Camera Active", Point(20, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);

        imshow("Веб-камера (HW6)", frame);

        char c = (char)waitKey(25);
        if (c == 27) break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}