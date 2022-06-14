#ifndef TRIANGLE_FILTER_H
#define TRIANGLE_FILTER_H

#include "Filter.h"

class TriangleFilter : public Filter {
public:
    TriangleFilter(const Eigen::Vector2f& radius);
    ~TriangleFilter();
    float evaluate(const Eigen::Vector2f& p) const override;
};

#endif