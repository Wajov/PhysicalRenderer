#include "Filter.h"

Filter::Filter(const Eigen::Vector2f& radius) :
    radius(radius),
    invRadius(1.0f / radius.x(), 1.0f / radius.y()) {}

Filter::~Filter() {}

Eigen::Vector2f Filter::getRadius() const {
    return radius;
}

Eigen::Vector2f Filter::getInvRadius() const {
    return invRadius;
}
