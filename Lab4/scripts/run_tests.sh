#!/bin/bash

cd "$(dirname "$0")/.." || exit

mkdir -p build
cd build || exit

echo "Building tests..."
cmake ..
make

echo "Copying test assets..."
cp ../picture/test_face.jpg . 2>/dev/null

echo "Running Google Tests..."
./run_tests