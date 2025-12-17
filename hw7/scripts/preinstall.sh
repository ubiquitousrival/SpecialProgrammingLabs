#!/bin/bash

cd "$(dirname "$0")/.." || exit

echo "Installing dependencies..."
sudo apt-get update
sudo apt-get install -y build-essential cmake libopencv-dev wget
echo "Dependencies installed."

echo "Downloading models..."
mkdir -p models

PROTO_URL="https://raw.githubusercontent.com/opencv/opencv/master/samples/dnn/face_detector/deploy.prototxt"
MODEL_URL="https://raw.githubusercontent.com/opencv/opencv_3rdparty/dnn_samples_face_detector_20170830/res10_300x300_ssd_iter_140000.caffemodel"

if [ ! -f "models/deploy.prototxt" ]; then
    wget -O models/deploy.prototxt "$PROTO_URL"
fi

if [ ! -f "models/res10_300x300_ssd_iter_140000.caffemodel" ]; then
    wget -O models/res10_300x300_ssd_iter_140000.caffemodel "$MODEL_URL"
fi

echo "Models downloaded successfully."