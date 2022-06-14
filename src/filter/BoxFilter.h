#ifndef BOX_FILTER_H
#define BOX_FILTER_H

#include "Filter.h"

class BoxFilter : public Filter {
public:
    BoxFilter(const Eigen::Vector2f& radius);
    ~BoxFilter();
    float evaluate(const Eigen::Vector2f& p) const override;
};

#endif