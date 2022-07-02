#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Dense>

#include "Bounds.h"
#include "Ray.h"

class Transform {
private:
    Eigen::Matrix4f m, invM;

public:
    Transform();
    Transform(const Eigen::Matrix4f& m);
    Transform(const Eigen::Matrix4f& m, const Eigen::Matrix4f& invM);
    Transform(const Transform& transform);
    ~Transform();
    Transform operator*(const Transform& transform) const;
    Eigen::Vector3f transformPoint(const Eigen::Vector3f& p) const;
    Eigen::Vector3f transformVector(const Eigen::Vector3f& v) const;
    Bounds3f transformBounds(const Bounds3f& b) const;
    Ray transformRay(const Ray& r) const;
    RayDifferential transformRayDifferential(const RayDifferential& r) const;
    Eigen::Vector3f transformPoint(const Eigen::Vector3f& p, Eigen::Vector3f& pError) const;
    Eigen::Vector3f transformVector(const Eigen::Vector3f& v, Eigen::Vector3f& vError) const;
    Ray transformRay(const Ray& r, Eigen::Vector3f& oError, Eigen::Vector3f& dError) const;
    Transform inverse() const;
};

#endif