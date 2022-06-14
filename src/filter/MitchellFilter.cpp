#include "MitchellFilter.h"

MitchellFilter::MitchellFilter(const Eigen::Vector2f& radius, float B, float C) :
    Filter(radius),
    B(B),
    C(C) {}

MitchellFilter::~MitchellFilter() {}

float MitchellFilter::mitchell(float x) const {
    x = std::abs(2.0f * x);
    if (x > 1.0f)
        return ((-B - 6.0f * C) * x * x * x + (6.0f * B + 30.0f * C) * x * x + (-12.0f * B - 48.0f * C) * x + (8.0f * B + 24.0f * C)) / 6.0f;
    else
        return ((12.0f - 9.0f * B - 6.0f * C) * x * x * x + (-18.0f + 12.0f * B + 6.0f * C) * x * x + (6.0f - 2.0f * B)) / 6.0f;
}

float MitchellFilter::evaluate(const Eigen::Vector2f& p) const {
    return mitchell(p.x() * invRadius.x()) * mitchell(p.y() * invRadius.y());
}