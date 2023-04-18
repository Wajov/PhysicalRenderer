#include "Sphere.h"

Sphere::Sphere(const Transform& objectToWorld, const Transform& worldToObject, bool reverseOrientation, float radius, float zMin, float zMax, float phiMax) :
    Shape(objectToWorld, worldToObject, reverseOrientation),
    radius(radius),
    zMin(std::clamp(std::min(zMin, zMax), -radius, radius)),
    zMax(std::clamp(std::max(zMin, zMax), -radius, radius)),
    thetaMin(std::acos(std::clamp(std::min(zMin, zMax) / radius, -1.0f, 1.0f))),
    thetaMax(std::acos(std::clamp(std::max(zMin, zMax) / radius, -1.0f, 1.0f))),
    phiMax(radian(std::clamp(phiMax, 0.0f, 360.0f))) {}

Sphere::~Sphere() {}

Bounds3f Sphere::objectBounds() const {
    return Bounds3f(Eigen::Vector3f(-radius, -radius, zMin), Eigen::Vector3f(radius, radius, zMax));
}

bool Sphere::intersect(const Ray& r, float& tHit, int& interaction, bool testAlphaTexture) const {
    Eigen::Vector3f oError, dError;
    Ray ray = worldToObject.transformRay(ray, oError, dError);

    ErrorFloat ox(ray.o.x(), oError.x()), oy(ray.o.y(), oError.y()), oz(ray.o.z(), oError.z());
    ErrorFloat dx(ray.d.x(), dError.x()), dy(ray.d.y(), dError.y()), dz(ray.d.z(), dError.z());
    ErrorFloat a = sqr(dx) + sqr(dy) + sqr(dz);
    ErrorFloat b = ErrorFloat(2.0f) * (ox * dx + oy * dy + oz * dz);
    ErrorFloat c = sqr(ox) + sqr(oy) + sqr(oz) - sqr(ErrorFloat(radius));

    ErrorFloat t0, t1;
    if (!solveQuadratic(a, b, c, t0, t1))
        return false;
    if (t0.getUpper() > ray.tMax || t1.getLower() <= 0.0f)
        return false;

    ErrorFloat tShapeHit = t0;
    if (tShapeHit.getLower() <= 0.0f) {
        tShapeHit = t1;
        if (tShapeHit.getUpper() > ray.tMax)
            return false;
    }

    Eigen::Vector3f pHit = ray((float)tShapeHit);
    pHit *= radius / pHit.norm();
    if (pHit.x() == 0.0f && pHit.y() == 0.0f)
        pHit.x() = 1e-5f * radius;
    float phi = std::atan2(pHit.y(), pHit.x());
    if (phi < 0.0f)
        phi += 2 * PI;

    // TODO
}
