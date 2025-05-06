cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(
    image_processor
    image_processor.cpp
    parser.cpp
    image.cpp
    ./filters/crop.cpp
    ./filters/grayscale.cpp
    ./filters/negative.cpp
    ./filters/a_matrix_filter.cpp
    ./filters/sharpen.cpp
    ./filters/edge.cpp
)
