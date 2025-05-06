#include "sharpen.h"

Image Sharpening::Apply(const Image& image) {
    return ApplyMatrixFilter(image, {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}});
}