#include "Camera.h"

Camera::Camera(const Transform& cameraToWorld, float shutterOpen, float shutterClose, Film* film, Medium* medium) :
    cameraToWorld(cameraToWorld),
    shutterOpen(shutterOpen),
    shutterClose(shutterClose),
    medium(medium) {}

Camera::~Camera() {}