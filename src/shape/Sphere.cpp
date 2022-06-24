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

bool Sphere::intersect(const Ray& ray, float& tHit, int& interaction, bool testAlphaTexture) const {
    return false;
}
