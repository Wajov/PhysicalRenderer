#ifndef MITCHELL_FILTER_H
#define MITCHELL_FILTER_H

#include "Filter.h"

class MitchellFilter : public Filter {
private:
    float B, C;
    float mitchell(float x) const;

public:
    MitchellFilter(const Eigen::Vector2f& radius, float B, float C);
    ~MitchellFilter();
    float evaluate(const Eigen::Vector2f& p) const override;
};

#endif