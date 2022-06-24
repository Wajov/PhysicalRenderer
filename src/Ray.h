#ifndef RAY_H
#define RAY_H

#include <Eigen/Dense>

#include "MathHelper.h"
#include "medium/Medium.h"

class Ray {
public:
    Eigen::Vector3f o, d;
    float tMax, time;
    Medium* medium;
    Ray();
    Ray(const Eigen::Vector3f& o, const Eigen::Vector3f&d, float tMax = INF, float time = 0.0f, Medium* medium = nullptr);
    Eigen::Vector3f operator()(float t) const;
    ~Ray();
};

class RayDifferential : public Ray {
public:
    bool hasDifferentials;
    Eigen::Vector3f rxOrigin, ryOrigin, rxDirection, ryDirection;
    RayDifferential();
    RayDifferential(const Eigen::Vector3f& o, const Eigen::Vector3f&d, float tMax = INF, float time = 0.0f, Medium* medium = nullptr);
    ~RayDifferential();
};

#endif