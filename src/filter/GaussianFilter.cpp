#include "GaussianFilter.h"

GaussianFilter::GaussianFilter(const Eigen::Vector2f& radius, float alpha) :
    Filter(radius),
    alpha(alpha),
    expX(std::exp(-alpha * sqr(radius.x()))),
    expY(std::exp(-alpha * sqr(radius.y()))) {}

GaussianFilter::~GaussianFilter() {}

float GaussianFilter::gaussian(float d, float exp) const {
    return std::max(0.0f, std::exp(-alpha * sqr(d)) - exp);
}

float GaussianFilter::evaluate(const Eigen::Vector2f& p) const {
    return gaussian(p.x(), expX) * gaussian(p.y(), expY);
}