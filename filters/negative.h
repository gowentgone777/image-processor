#pragma once
#include <cstdint>
#include "a_filter.h"
#include "../image.h"

class Negative : public Filter {
public:
    Negative(){};
    Image Apply(const Image& image) override;
};