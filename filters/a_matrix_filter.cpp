#include "a_matrix_filter.h"

Image ApplyMatrixFilter(const Image& image, const std::vector<std::vector<float>>& matrix) {
    int32_t h_radius = static_cast<int32_t>(matrix.size() / 2);
    int32_t w_radius = static_cast<int32_t>(matrix[0].size() / 2);
    Image new_image(image.GetHeight(), image.GetWidth());
    for (int32_t y = 0; y < image.GetHeight(); ++y) {
        for (int32_t x = 0; x < image.GetWidth(); ++x) {
            float r = 0;
            float g = 0;
            float b = 0;
            for (int32_t dy = -h_radius; dy <= h_radius; ++dy) {
                for (int32_t dx = -w_radius; dx <= w_radius; ++dx) {
                    int32_t cur_x = std::min(std::max(x + dx, 0), image.GetWidth() - 1);
                    int32_t cur_y = std::min(std::max(y + dy, 0), image.GetHeight() - 1);
                    if (cur_x >= 0 && cur_x < image.GetWidth() && cur_y >= 0 && cur_y < image.GetHeight()) {
                        r += image.GetColor(cur_x, cur_y).red_ * matrix[dy + h_radius][dx + w_radius];
                        g += image.GetColor(cur_x, cur_y).green_ * matrix[dy + h_radius][dx + w_radius];
                        b += image.GetColor(cur_x, cur_y).blue_ * matrix[dy + h_radius][dx + w_radius];
                    }
                }
            }
            r = std::min(std::max(r, 0.0f), 1.0f);
            g = std::min(std::max(g, 0.0f), 1.0f);
            b = std::min(std::max(b, 0.0f), 1.0f);
            if (x >= 0 && x < new_image.GetWidth() && y >= 0 && y < new_image.GetHeight()) {
                new_image.SetColor(x, y, Color(r, g, b));
            }
        }
    }
    return new_image;
}