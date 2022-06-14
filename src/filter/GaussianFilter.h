#ifndef GAUSSIAN_FILTER_H
#define GAUSSIAN_FILTER_H

#include "MathHelper.h"
#include "Filter.h"

class GaussianFilter : public Filter {
private:
    float alpha, expX, expY;
    float gaussian(float d, float exp) const;

public:
    GaussianFilter(const Eigen::Vector2f& radius, float alpha);
    ~GaussianFilter();
    float evaluate(const Eigen::Vector2f& p) const override;
};

#endif