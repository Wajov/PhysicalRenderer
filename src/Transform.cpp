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
    Eigen::Vector3f oError;
    Eigen::Vector3f o = transformPoint(r.o, oError);
    Eigen::Vector3f d = transformVector(r.d);
    float l2 = d.squaredNorm();
    float tMax = r.tMax;
    if (l2 > 0.0f) {
        float dt = abs(d).dot(oError) / l2;
        o += d * dt;
        tMax -= dt;
    }
    return Ray(o, d, tMax, r.time, r.medium);
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

Eigen::Vector3f Transform::transformPoint(const Eigen::Vector3f& p, Eigen::Vector3f& pError) const {
    float x = p.x(), y = p.y(), z = p.z();

    float px = m(0, 0) * x + m(0, 1) * y + m(0, 2) * z + m(0, 3);
    float py = m(1, 0) * x + m(1, 1) * y + m(1, 2) * z + m(1, 3);
    float pz = m(2, 0) * x + m(2, 1) * y + m(2, 2) * z + m(2, 3);
    float pw = m(3, 0) * x + m(3, 1) * y + m(3, 2) * z + m(3, 3);

    float xAbsSum = std::abs(m(0, 0) * x) + std::abs(m(0, 1) * y) + std::abs(m(0, 2) * z) + std::abs(m(0, 3));
    float yAbsSum = std::abs(m(1, 0) * x) + std::abs(m(1, 1) * y) + std::abs(m(1, 2) * z) + std::abs(m(2, 3));
    float zAbsSum = std::abs(m(2, 0) * x) + std::abs(m(2, 1) * y) + std::abs(m(2, 2) * z) + std::abs(m(2, 3));
    pError = gamma(3) * Eigen::Vector3f(xAbsSum, yAbsSum, zAbsSum);

    if (pw == 1.0f)
        return Eigen::Vector3f(px, py, pz);
    else
        return Eigen::Vector3f(px, py, pz) / pw;
}

Eigen::Vector3f Transform::transformVector(const Eigen::Vector3f& v, Eigen::Vector3f& vError) const {
    float x = v.x(), y = v.y(), z = v.z();

    float vx = m(0, 0) * x + m(0, 1) * y + m(0, 2) * z;
    float vy = m(1, 0) * x + m(1, 1) * y + m(1, 2) * z;
    float vz = m(2, 0) * x + m(2, 1) * y + m(2, 2) * z;

    float xAbsSum = std::abs(m(0, 0) * x) + std::abs(m(0, 1) * y) + std::abs(m(0, 2) * z);
    float yAbsSum = std::abs(m(1, 0) * x) + std::abs(m(1, 1) * y) + std::abs(m(1, 2) * z);
    float zAbsSum = std::abs(m(2, 0) * x) + std::abs(m(2, 1) * y) + std::abs(m(2, 2) * z);
    vError = gamma(3) * Eigen::Vector3f(xAbsSum, yAbsSum, zAbsSum);

    return Eigen::Vector3f(vx, vy, vz);
}

Ray Transform::transformRay(const Ray& r, Eigen::Vector3f& oError, Eigen::Vector3f& dError) const {
    Eigen::Vector3f o = transformPoint(r.o, oError);
    Eigen::Vector3f d = transformVector(r.d, dError);
    float tMax = r.tMax;
    float l2 = d.squaredNorm();
    if (l2 > 0.0f) {
        float dt = abs(d).dot(oError) / l2;
        o += d * dt;
    }
    return Ray(o, d, tMax, r.time, r.medium);
}

Transform Transform::inverse() const {
    return Transform(invM, m);
}