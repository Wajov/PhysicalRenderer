#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(const Transform& cameraToWorld, const Bounds2f& screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance, Film* film, Medium* medium) :
    ProjectiveCamera(cameraToWorld, orthographic(0.0f, 1.0f), screenWindow, shutterOpen, shutterClose, lensRadius, focalDistance, film, medium) {
    dxCamera = rasterToCamera.transformVector(Eigen::Vector3f(1.0f, 0.0f, 0.0f));
    dyCamera = rasterToCamera.transformVector(Eigen::Vector3f(0.0f, 1.0f, 0.0f));
}

OrthographicCamera::~OrthographicCamera() {}

Transform OrthographicCamera::orthographic(float zNear, float zFar) {
    return scale(Eigen::Vector3f(1.0f, 1.0f, 1.0f / (zFar - zNear))) * translate(Eigen::Vector3f(0.0f, 0.0f, -zNear));
}

float OrthographicCamera::generateRayDifferential(const CameraSample& sample, RayDifferential& ray) const {
    Eigen::Vector3f pFilm(sample.pFilm.x(), sample.pFilm.y(), 0.0f);
    Eigen::Vector3f pCamera = rasterToCamera.transformPoint(pFilm);
    ray = RayDifferential(pCamera, Eigen::Vector3f(0.0f, 0.0f, 1.0f));

    if (lensRadius > 0.0f) {
        Eigen::Vector2f pLens = lensRadius * concentricSampleDisk(sample.pLens);
        float t = focalDistance / ray.d.z();

        Eigen::Vector3f pFocus = ray(t);
        ray.o = Eigen::Vector3f(pLens.x(), pLens.y(), 0.0f);
        ray.d = (pFocus - ray.o).normalized();

        pFocus = pCamera + dxCamera + Eigen::Vector3f(0.0f, 0.0f, t);
        ray.rxOrigin = Eigen::Vector3f(pLens.x(), pLens.y(), 0.0f);
        ray.rxDirection = (pFocus - ray.rxOrigin).normalized();

        pFocus = pCamera + dyCamera + Eigen::Vector3f(0.0f, 0.0f, t);
        ray.ryOrigin = Eigen::Vector3f(pLens.x(), pLens.y(), 0.0f);
        ray.ryDirection = (pFocus - ray.ryOrigin).normalized();
    } else {
        ray.rxOrigin = ray.o + dxCamera;
        ray.ryOrigin = ray.o + dyCamera;
        ray.rxDirection = ray.ryDirection = ray.d;
    }

    ray.time = linearInterpolate(sample.time, shutterOpen, shutterClose);
    ray.medium = medium;
    ray = cameraToWorld.transformRayDifferential(ray);
    ray.hasDifferentials = true;
    return 1.0f;
}
