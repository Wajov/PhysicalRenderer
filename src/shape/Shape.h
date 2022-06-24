#ifndef SHAPE_H
#define SHAPE_H

#include "Bounds.h"
#include "Transform.h"

class Shape {
protected:
    Transform objectToWorld, worldToObject;
    bool reverseOrientation, transformSwapHandedness;

public:
    Shape(const Transform& objectToWorld, const Transform& worldToObject, bool reverseOrientation);
    ~Shape();
    virtual Bounds3f objectBounds() const = 0;
    virtual Bounds3f worldBounds() const;
    virtual bool intersect(const Ray& ray, float& tHit, SurfaceInteraction& interaction, bool testAlphaTexture) const = 0;
};

#endif