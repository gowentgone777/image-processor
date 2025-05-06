#pragma once

#include <cstdint>
#include "a_filter.h"

class Crop : public Filter {
public:
    Crop(int32_t new_width, int32_t new_height);
    Image Apply(const Image& image) override;

private:
    const int32_t new_width_;
    const int32_t new_height_;
};