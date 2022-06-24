#include "SamplerIntegrator.h"

SamplerIntegrator::SamplerIntegrator(Camera* camera, Sampler* sampler, const Bounds2i& pixelBounds) :
    Integrator(),
    camera(camera),
    sampler(sampler),
    pixelBounds(pixelBounds) {}

SamplerIntegrator::~SamplerIntegrator() {}

void SamplerIntegrator::render(const Scene* scene) {
    preprocess(scene);

    Bounds2i sampleBounds = film->getSampleBounds();
    for (int y = sampleBounds.pMin.y(); y <= sampleBounds.pMax.y(); y++)
        for (int x = sampleBounds.pMin.x(); x <= sampleBounds.pMin.x(); x++) {
            Eigen::Vector2i pixel(x, y);
            sampler->startPixel(pixel);
            CameraSample cameraSample = sampler->getCameraSample(pixel);

            RayDifferential ray;
            float sampleWeight = camera->generateRayDifferential(cameraSample, ray);
            ray.scaleDifferentials(1.0f / std::sqrt((float)sampler->getSamplesPerPixel()));

            RGBSpectrum L;
            if (sampleWeight > 0.0f)
                L = Li(ray, scene, 0);

            camera->addSample(cameraSample.pFilm, L, sampleWeight);
        }

    camera->writeImage();
}
