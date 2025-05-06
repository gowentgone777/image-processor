#pragma once
#include "a_matrix_filter.h"

class Sharpening : public Filter {
public:
    Sharpening(){};
    Image Apply(const Image& image) override;
};