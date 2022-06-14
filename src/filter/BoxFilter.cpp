#include "BoxFilter.h"

BoxFilter::BoxFilter(const Eigen::Vector2f& radius) :
    Filter(radius) {}

BoxFilter::~BoxFilter() {}

float BoxFilter::evaluate(const Eigen::Vector2f& p) const {
    return 1.0f;
}
