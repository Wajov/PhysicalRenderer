#ifndef SINC_FILTER_H
#define SINC_FILTER_H

#include "MathHelper.h"
#include "Filter.h"

class SincFilter : public Filter {
private:
    float tau;
    float sinc(float x) const;
    float windowedSinc(float x, float radius) const;

public:
    SincFilter(const Eigen::Vector2f& radius, float tau);
    ~SincFilter();
    float evaluate(const Eigen::Vector2f& p) const override;
};


#endif