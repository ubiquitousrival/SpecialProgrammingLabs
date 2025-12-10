#!/bin/bash
# Генеруємо файли збірки у папці build (S = Source, B = Build)
cmake -S . -B build

# Компілюємо проект (паралельно, ключ -j пришвидшує процес)
cmake --build build -j

echo "Build finished."