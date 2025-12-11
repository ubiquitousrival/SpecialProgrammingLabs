#!/bin/bash
cd "$(dirname "$0")/.."

echo "Installing dependencies (Linux only)..."
if [ -x "$(command -v apt-get)" ]; then
    sudo apt-get update
    sudo apt-get install -y build-essential cmake git libopencv-dev wget
fi

echo "Creating resources directory..."
mkdir -p resources

echo "Downloading Face Detection Model..."
wget -nc -O resources/res10_300x300_ssd_iter_140000.caffemodel https://raw.githubusercontent.com/opencv/opencv_3rdparty/dnn_samples_face_detector_20170830/res10_300x300_ssd_iter_140000.caffemodel

echo "Done."