#ifndef SPHERE_H
#define SPHERE_H

#include "MathHelper.h"
#include "Shape.h"
#include "ErrorFloat.h"

class Sphere : public Shape {
private:
    float radius, zMin, zMax, thetaMin, thetaMax, phiMax;

public:
    Sphere(const Transform& objectToWorld, const Transform& worldToObject, bool reverseOrientation, float radius, float zMin, float zMax, float phiMax);
    ~Sphere();
    Bounds3f objectBounds() const override;
    bool intersect(const Ray& r, float& tHit, int& interaction, bool testAlphaTexture) const override;
};


#endif