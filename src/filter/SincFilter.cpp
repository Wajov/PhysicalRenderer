#include "SincFilter.h"

SincFilter::SincFilter(const Eigen::Vector2f& radius, float tau) :
    Filter(radius),
    tau(tau) {}

SincFilter::~SincFilter() {}

float SincFilter::sinc(float x) const {
    x = std::abs(x);
    if (x < 1e-5)
        return 1.0f;
    return std::sin(PI * x) / (PI * x);
}

float SincFilter::windowedSinc(float x, float radius) const {
    x = std::abs(x);
    if (x > radius)
        return 0.0f;
    return sinc(x) * sinc(x / tau);
}

float SincFilter::evaluate(const Eigen::Vector2f& p) const {
    return windowedSinc(p.x(), radius.x()) * windowedSinc(p.y(), radius.y());
}
