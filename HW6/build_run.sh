#!/bin/bash
OUTPUT="camera_app"
SOURCE="main.cpp"

if ! command -v g++ &> /dev/null
then
    echo "Помилка: g++ не знайдено."
    exit 1
fi

g++ $SOURCE -o $OUTPUT

if [ $? -eq 0 ]; then
    ./$OUTPUT
else
    echo "--- Помилка компіляції ---"
    exit 1
fi