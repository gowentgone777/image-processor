# Image Processor

This project is a console apllication that allows applying some basic filters to .BMP images

## Supported image format

The input file must have 24-bit BMP format 
## Prerequisites

- CMake installed
- C++ compiler (e.g., GCC, Clang, MSVC)

## Usage 
1. Clone or Navigate to Project Directory
    ```bash
    git clone <project-repository-url>
    ```

2. Generate Makefile with CMake
    ```bash
    cmake -B build -S . -D CMAKE_BUILD_TYPE=Release
    ```
3. Run executable:
    ```bash
    ./image_processor <input file> <output file> <filter flag with respective arguments>
    ```

## Avalibale filters

### Crop ```-crop <width> <height>```
Crops the image to the specified width and height. The top left part of the image is used.
If the requested width or height exceeds the dimensions of the original image, the available portion of the image is returned.

### Grayscale ```-gs```
Converts an image to grayscale.

### Negative ```-neg```
Converts an image to negative.

### Sharpening ```-sharp```
Increases sharpness of the image.

### Edge Detection ```-edge <threshold>```
Detects edges. Pixels with a value exceeding the ```threshold``` are colored white, the rest - black.
