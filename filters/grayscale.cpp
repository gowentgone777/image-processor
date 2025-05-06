#include "grayscale.h"

Image Grayscale::Apply(const Image& image) {
    Image new_image(image.GetHeight(), image.GetWidth());
    for (int32_t y = 0; y < new_image.GetHeight(); ++y) {
        for (int32_t x = 0; x < new_image.GetWidth(); ++x) {
            Color new_color = image.GetColor(x, y);
            new_color.red_ = new_color.green_ = new_color.blue_ =
                coeff_red_ * new_color.red_ + coeff_green_ * new_color.green_ + coeff_blue_ * new_color.blue_;
            new_image.SetColor(x, y, new_color);
        }
    }
    return new_image;
}