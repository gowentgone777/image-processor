#include "negative.h"

Image Negative::Apply(const Image& image) {
    Image new_image(image.GetHeight(), image.GetWidth());
    for (int32_t y = 0; y < new_image.GetHeight(); ++y) {
        for (int32_t x = 0; x < new_image.GetWidth(); ++x) {
            Color new_color = image.GetColor(x, y);
            new_color.red_ = 1 - new_color.red_;
            new_color.green_ = 1 - new_color.green_;
            new_color.blue_ = 1 - new_color.blue_;
            new_image.SetColor(x, y, new_color);
        }
    }
    return new_image;
}