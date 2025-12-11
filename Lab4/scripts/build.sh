#!/bin/bash
cd "$(dirname "$0")/.."

echo "Building project..."
rm -rf build
mkdir build
cd build

cmake ..
make -j$(nproc)