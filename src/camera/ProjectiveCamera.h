#ifndef PROJECTIVE_CAMERA_H
#define PROJECTIVE_CAMERA_H

#include "TransformHelper.h"
#include "SampleHelper.h"
#include "Camera.h"

class ProjectiveCamera : public Camera {
protected:
    Transform cameraToScreen, rasterToCamera, screenToRaster, rasterToScreen;
    float lensRadius, focalDistance;

public:
    ProjectiveCamera(const Transform& cameraToWorld, const Transform& cameraToScreen, const Bounds2f& screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance, Film* film, Medium* medium);
    ~ProjectiveCamera();
};


#endif