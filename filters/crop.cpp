#include "crop.h"

Crop::Crop(int32_t new_width, int32_t new_height) : new_width_(new_width), new_height_(new_height) {
}

Image Crop::Apply(const Image& image) {
    Image new_image(std::min(new_height_, image.GetHeight()), std::min(new_width_, image.GetWidth()));
    int32_t offset = new_image.GetHeight() < image.GetHeight() ? image.GetHeight() - new_image.GetHeight() : 0;
    for (int32_t y = 0; y < new_image.GetHeight(); ++y) {
        for (int32_t x = 0; x < new_image.GetWidth(); ++x) {
            new_image.SetColor(x, y, image.GetColor(x, y + offset));
        }
    }
    return new_image;
}