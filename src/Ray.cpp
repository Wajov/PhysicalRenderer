#include "Ray.h"

Ray::Ray() :
    o(0.0f, 0.0f, 0.0f),
    d(0.0f, 0.0f, 0.0f),
    tMax(INF),
    time(0.0f),
    medium(nullptr) {}

Ray::Ray(const Eigen::Vector3f& o, const Eigen::Vector3f& d, float tMax, float time, Medium* medium) :
    o(o),
    d(d),
    tMax(tMax),
    time(time),
    medium(medium) {}

Eigen::Vector3f Ray::operator()(float t) const {
    return o + d * t;
}

Ray::~Ray() {}

RayDifferential::RayDifferential() :
    Ray(),
    hasDifferentials(false) {}

RayDifferential::RayDifferential(const Eigen::Vector3f& o, const Eigen::Vector3f& d, float tMax, float time, Medium* medium) :
    Ray(o, d, tMax, time, medium),
    hasDifferentials(false) {}

RayDifferential::~RayDifferential() {}