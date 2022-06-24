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

Eigen::Vector3f Transform::transformPoint(const Eigen::Vector3f& p) const {
    Eigen::Vector4f t = m * Eigen::Vector4f(p.x(), p.y(), p.z(), 1.0f);
    return Eigen::Vector3f(t.x(), t.y(), t.z());
}

Eigen::Vector3f Transform::transformVector(const Eigen::Vector3f& v) const {
    Eigen::Vector4f t = m * Eigen::Vector4f(v.x(), v.y(), v.z(), 0.0f);
    return Eigen::Vector3f(t.x(), t.y(), t.z());
}

Bounds3f Transform::transformBounds(const Bounds3f& b) const {
    Bounds3f ans(transformPoint(b.pMin));
    ans.add(transformPoint(Eigen::Vector3f(b.pMin.x(), b.pMin.y(), b.pMax.z())));
    ans.add(transformPoint(Eigen::Vector3f(b.pMin.x(), b.pMax.y(), b.pMin.z())));
    ans.add(transformPoint(Eigen::Vector3f(b.pMin.x(), b.pMax.y(), b.pMax.z())));
    ans.add(transformPoint(Eigen::Vector3f(b.pMax.x(), b.pMin.y(), b.pMin.z())));
    ans.add(transformPoint(Eigen::Vector3f(b.pMax.x(), b.pMin.y(), b.pMax.z())));
    ans.add(transformPoint(Eigen::Vector3f(b.pMax.x(), b.pMax.y(), b.pMin.z())));
    ans.add(transformPoint(Eigen::Vector3f(b.pMax.x(), b.pMax.y(), b.pMax.z())));
    return ans;
}

Ray Transform::transformRay(const Ray& r) const {
    Eigen::Vector3f o = transformPoint(r.o);
    Eigen::Vector3f d = transformVector(r.d);
    float l2 = d.squaredNorm();
    float tMax = r.tMax;
    if (l2 > 0.0f) {
        // TODO
    }
    return Ray();
}

RayDifferential Transform::transformRayDifferential(const RayDifferential& r) const {
    Ray ray = transformRay(Ray(r));
    RayDifferential ans(ray.o, ray.d, ray.tMax, ray.time, ray.medium);
    ans.hasDifferentials = r.hasDifferentials;
    ans.rxOrigin = r.rxOrigin;
    ans.ryOrigin = r.ryOrigin;
    ans.rxDirection = r.rxDirection;
    ans.ryDirection = r.ryDirection;
    return ans;
}

Transform Transform::inverse() const {
    return Transform(invM, m);
}
