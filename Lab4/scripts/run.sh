#!/bin/bash

cd "$(dirname "$0")/.." || exit

APP_NAME="lab4_app"

if [ -f "./build/$APP_NAME" ]; then
    echo "Starting $APP_NAME..."
    ./build/$APP_NAME
else
    echo "Error: Executable './build/$APP_NAME' not found."
    echo "Current contents of build folder:"
    ls -F ./build/ 2>/dev/null
    echo "Please run './scripts/build.sh' first."
    exit 1
fi