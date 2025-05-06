#include "edge.h"

Edge::Edge(float threshold) : threshold_(threshold) {  // NOLINT
}

Image Edge::Apply(const Image &image) {
    Grayscale grayscale;
    Image gray_image = grayscale.Apply(image);
    Image result = ApplyMatrixFilter(gray_image, {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});  // NOLINT
    for (int32_t i = 0; i < result.GetWidth(); ++i) {
        for (int32_t j = 0; j < result.GetHeight(); ++j) {
            if (result.GetColor(i, j).red_ > threshold_) {
                result.SetColor(i, j, {1, 1, 1});
            } else {
                result.SetColor(i, j, {0, 0, 0});
            }
        }
    }
    return result;
}