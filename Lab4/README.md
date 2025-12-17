# Lab 4: Multithreaded Face Detection

Advanced C++ OpenCV project with asynchronous face detection.

## Features

- **Threads**: Detection runs in a background thread using `std::thread`.
- **Synchronization**: `std::mutex` and `std::atomic` ensure thread safety.
- **Performance**: UI remains responsive even with heavy detection tasks.
- **Effects**: Interactive filters (Sepia, Pixelize, Canny, etc.).

## Build & Run

To build and run the project, use the scripts provided in the `scripts` directory:

1.  **Install dependencies (if needed):**
    ```bash
    ./scripts/preinstall.sh
    ```

2.  **Build the project:**
    ```bash
    ./scripts/build.sh
    ```

3.  **Run the application:**
    ```bash
    ./scripts/run.sh
    ```

## Controls

- **F**: Toggle Face Detection
- **1-8**: Visual Effects
- **Sliders**: Brightness & Effect intensity
