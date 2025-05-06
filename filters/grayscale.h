#pragma once
#include <cstdint>
#include "a_filter.h"
#include "../image.h"

class Grayscale : public Filter {
public:
    Grayscale(){};
    Image Apply(const Image& image) override;

private:
    const float coeff_red_ = 0.299;
    const float coeff_green_ = 0.587;
    const float coeff_blue_ = 0.114;
};