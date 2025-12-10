#!/bin/bash
# Створюємо папку та генеруємо файли збірки (без cd)
cmake -S . -B build
# Запускаємо компіляцію паралельно (-j)
cmake --build build -j
echo "Build finished."