#include "Transform.h"

Transform::Transform() :
    m(Eigen::Matrix4f::Identity()),
    invM(Eigen::Matrix4f::Identity()) {}

Transform::Transform(const Eigen::Matrix4f& m) :
    m(m),
    invM(m.inverse()) {}

Transform::Transform(const Eigen::Matrix4f& m, const Eigen::Matrix4f& invM) :
    m(m),
    invM(invM) {}

Transform::Transform(const Transform& transform) :
    m(transform.m),
    invM(transform.invM) {}

Transform::~Transform() {}

Transform Transform::operator*(const Transform& transform) const {
    return Transform(m * transform.m, transform.invM * invM);
}

Transform Transform::inverse() const {
    return Transform(invM, m);
}
