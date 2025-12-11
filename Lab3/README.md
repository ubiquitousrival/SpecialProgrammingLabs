# Lab 3: OpenCV Filters

## Requirements
- OS: Ubuntu 20.04+
- Dependencies: cmake, g++, libopencv-dev

## Installation & Build
1. Run the build script:
   ./build.sh

## Usage
1. Run the app:
   ./run.sh

## Controls
- **Slider 1 (Brightness)**: Adjusts image brightness globally.
- **Slider 2 (Effect)**: Adjusts intensity for specific modes (Blur, Canny, Sepia, Pixelize).
- **Keys**:
  - '1': Normal Mode
  - '2': Invert Colors
  - '3': Gaussian Blur (Use Effect slider)
  - '4': Canny Edge (Use Effect slider for threshold)
  - '5': Sobel Filter
  - '6': Mirror
  - '7': Sepia Effect (Use Effect slider for mixing)
  - '8': Pixelize Effect (Use Effect slider for pixel size)
- **ESC / q**: Exit
