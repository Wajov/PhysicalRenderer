#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Dense>

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
    Transform inverse() const;
};

#endif