#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"
#include "CameraSample.h"
#include "Film.h"
#include "medium/Medium.h"

class Camera {
protected:
    Transform cameraToWorld;
    float shutterOpen, shutterClose;
    Film* film;
    Medium* medium;

public:
    Camera(const Transform& cameraToWorld, float shutterOpen, float shutterClose, Film* film, Medium* medium);
    ~Camera();
    virtual float generateRay(const CameraSample& sample, Ray& ray) const = 0;
    virtual float generateRayDifferential(const CameraSample& sample, RayDifferential& ray) const = 0;
};

#endif