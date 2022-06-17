#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include "ProjectiveCamera.h"

class OrthographicCamera : public ProjectiveCamera {
private:
    Eigen::Vector3f dxCamera, dyCamera;

public:
    OrthographicCamera(const Transform& cameraToWorld, const Bounds2f& screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance, Film* film, Medium* medium);
    ~OrthographicCamera();

};


#endif