#!/bin/bash

cd "$(dirname "$0")/.." || exit

if [ -f "./build/Lab4" ]; then
    echo "Starting Lab4..."
    ./build/Lab4
else
    echo "Error: Executable './build/Lab4' not found."
    echo "Please run './scripts/build.sh' first."
    exit 1
fi