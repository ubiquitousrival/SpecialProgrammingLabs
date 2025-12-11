#!/bin/bash

cd "$(dirname "$0")/.." || exit

if [ -f "./build/Lab4" ]; then
    ./build/Lab4
else
    echo "Error: Executable not found. Please run scripts/build.sh first."
    exit 1
fi