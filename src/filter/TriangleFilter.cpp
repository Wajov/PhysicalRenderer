#include "TriangleFilter.h"

TriangleFilter::TriangleFilter(const Eigen::Vector2f& radius) :
    Filter(radius) {}

TriangleFilter::~TriangleFilter() {}

float TriangleFilter::evaluate(const Eigen::Vector2f& p) const {
    return std::max(0.0f, radius.x() - std::abs(p.x())) * std::max(0.0f, radius.y() - std::abs(p.y()));
}
