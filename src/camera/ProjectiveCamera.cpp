#include "ProjectiveCamera.h"

ProjectiveCamera::ProjectiveCamera(const Transform& cameraToWorld, const Transform& cameraToScreen, const Bounds2f& screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance, Film* film, Medium* medium) :
    Camera(cameraToWorld, shutterOpen, shutterClose, film, medium),
    cameraToScreen(cameraToScreen),
    lensRadius(lensRadius),
    focalDistance(focalDistance) {
    Eigen::Vector2i resolution = film->getResolution();
    screenToRaster = scale(Eigen::Vector3f((float)resolution.x(), (float)resolution.y(), 1.0f)) * scale(Eigen::Vector3f(1.0f / (screenWindow.pMax.x() - screenWindow.pMin.x()), 1.0f / (screenWindow.pMax.y() - screenWindow.pMin.y()), 1.0f)) * translate(Eigen::Vector3f(-screenWindow.pMin.x(), -screenWindow.pMin.y(), 1.0f));
    rasterToScreen = screenToRaster.inverse();
    rasterToCamera = cameraToScreen.inverse() * rasterToScreen;
}

ProjectiveCamera::~ProjectiveCamera() {

}
