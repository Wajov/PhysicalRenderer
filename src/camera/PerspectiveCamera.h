#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "SampleHelper.h"
#include "ProjectiveCamera.h"

class PerspectiveCamera : public ProjectiveCamera {
private:
    Eigen::Vector3f dxCamera, dyCamera;
    float A;
    inline static Transform perspective(float fov, float zNear, float zFar);

public:
    PerspectiveCamera(const Transform& cameraToWorld, const Bounds2f& screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance, float fov, Film* film, Medium* medium);
    ~PerspectiveCamera();
    float generateRayDifferential(const CameraSample& sample, RayDifferential& ray) const override;
};


#endif