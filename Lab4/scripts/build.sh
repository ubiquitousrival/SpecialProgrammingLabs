#!/bin/bash

cd "$(dirname "$0")/.." || exit

mkdir -p build
cd build || exit

cmake ..
make

echo "Copying models to build directory..."
cp ../models/deploy.prototxt .
cp ../models/res10_300x300_ssd_iter_140000.caffemodel .

echo "Build complete."