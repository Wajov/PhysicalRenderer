#include "Shape.h"

Shape::Shape(const Transform& objectToWorld, const Transform& worldToObject, bool reverseOrientation) :
    objectToWorld(objectToWorld),
    worldToObject(worldToObject),
    reverseOrientation(reverseOrientation),
    transformSwapHandedness(objectToWorld.swapHandedness()) {}

Shape::~Shape() {}

Bounds3f Shape::worldBounds() const {
    return objectToWorld.transformBounds(objectBounds());
}
