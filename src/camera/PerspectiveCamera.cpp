#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(const Transform& cameraToWorld, const Bounds2f& screenWindow, float shutterOpen, float shutterClose, float lensRadius, float focalDistance, float fov, Film* film, Medium* medium) :
    ProjectiveCamera(cameraToWorld, perspective(fov, 1e-2f, 1000.0f), screenWindow, shutterOpen, shutterClose, lensRadius, focalDistance, film, medium) {
    dxCamera = rasterToCamera.transformVector(Eigen::Vector3f(1.0f, 0.0f, 0.0f));
    dyCamera = rasterToCamera.transformVector(Eigen::Vector3f(0.0f, 1.0f, 0.0f));

    Eigen::Vector2i resolution = film->getResolution();
    Eigen::Vector3f pMin = rasterToCamera.transformPoint(Eigen::Vector3f(0.0f, 0.0f, 0.0f));
    Eigen::Vector3f pMax = rasterToCamera.transformPoint(Eigen::Vector3f((float)resolution.x(), (float)resolution.y(), 0.0f));
    pMin /= pMin.z();
    pMax /= pMax.z();
    A = std::abs(pMax.x() - pMin.x() * (pMax.y() - pMin.y()));
}

PerspectiveCamera::~PerspectiveCamera() {}

Transform PerspectiveCamera::perspective(float fov, float zNear, float zFar) {
    Eigen::Matrix4f m = Eigen::Matrix4f::Zero();
    m(0, 0) = m(1, 1) = m(3, 2) = 1.0f;
    m(2, 2) = zFar / (zFar - zNear);
    m(2, 3) = -zFar * zNear / (zFar - zNear);
    float invTan = 1 / std::tan(0.5f * radian(fov));
    return scale(Eigen::Vector3f(invTan, invTan, 1.0f)) * Transform(m);
}

float PerspectiveCamera::generateRayDifferential(const CameraSample& sample, RayDifferential& ray) const {
    Eigen::Vector3f pFilm(sample.pFilm.x(), sample.pFilm.y(), 0.0f);
    Eigen::Vector3f pCamera = rasterToCamera.transformPoint(pFilm);
    ray = RayDifferential(Eigen::Vector3f(0.0f, 0.0f, 0.0f), pCamera.normalized());

    if (lensRadius > 0.0f) {
        Eigen::Vector2f pLens = lensRadius * concentricSampleDisk(sample.pLens);

        float t = focalDistance / ray.d.z();
        Eigen::Vector3f pFocus = ray(t);
        ray.o = Eigen::Vector3f(pLens.x(), pLens.y(), 0.0f);
        ray.d = (pFocus - ray.o).normalized();

        Eigen::Vector3f dx = (pCamera + dxCamera).normalized();
        t = focalDistance / dx.z();
        pFocus = t * dx;
        ray.rxOrigin = Eigen::Vector3f(pLens.x(), pLens.y(), 0.0f);
        ray.rxDirection = (pFocus - ray.rxOrigin).normalized();

        Eigen::Vector3f dy = (pCamera + dyCamera).normalized();
        t = focalDistance / dy.z();
        pFocus = t * dy;
        ray.rxOrigin = Eigen::Vector3f(pLens.x(), pLens.y(), 0.0f);
        ray.ryDirection = (pFocus - ray.ryOrigin).normalized();
    } else {
        ray.rxOrigin = ray.ryOrigin = ray.o;
        ray.rxDirection = (pCamera + dxCamera).normalized();
        ray.ryDirection = (pCamera + dyCamera).normalized();
    }

    ray.time = linearInterpolate(sample.time, shutterOpen, shutterClose);
    ray.medium = medium;
    ray = cameraToWorld.transformRayDifferential(ray);
    ray.hasDifferentials = true;
    return 1.0f;
}
