#!/bin/bash

cd "$(dirname "$0")/.." || exit

mkdir -p build
cd build

cmake ..
make