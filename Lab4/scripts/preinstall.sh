#!/bin/bash

cd "$(dirname "$0")/.." || exit

echo "Installing dependencies..."
sudo apt-get update
sudo apt-get install -y build-essential cmake libopencv-dev
echo "Dependencies installed."