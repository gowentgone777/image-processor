#pragma once
#include "a_matrix_filter.h"
#include "grayscale.h"

class Edge : public Filter {
public:
    explicit Edge(float threshold);
    Image Apply(const Image &image) override;

private:
    float threshold_;
};