#!/bin/bash

cd "$(dirname "$0")/.." || exit

APP_NAME="lab4_app" 

if [ -f "./build/$APP_NAME" ]; then
    echo "Starting $APP_NAME..."

    cd build || exit

    ./$APP_NAME
else
    echo "Error: Executable not found inside build directory."
    echo "Please run './scripts/build.sh' first."
    exit 1
fi
