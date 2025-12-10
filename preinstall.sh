#!/bin/bash
echo "Installing dependencies..."
sudo apt-get update
sudo apt-get install -y build-essential cmake git libopencv-dev wget

echo "Downloading Face Detection Model..."
wget -O deploy.prototxt https://raw.githubusercontent.com/opencv/opencv/master/samples/dnn/face_detector/deploy.prototxt
wget -O res10_300x300_ssd_iter_140000.caffemodel https://raw.githubusercontent.com/opencv/opencv_3rdparty/dnn_samples_face_detector_20170830/res10_300x300_ssd_iter_140000.caffemodel

echo "Done."