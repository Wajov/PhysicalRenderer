#ifndef SAMPLER_INTEGRATOR_H
#define SAMPLER_INTEGRATOR_H

#include "Bounds.h"
#include "Integrator.h"
#include "camera/Camera.h"

class SamplerIntegrator : public Integrator {
protected:
    Camera* camera;
    Sampler* sampler;
    Bounds2i pixelBounds;

public:
    SamplerIntegrator(Camera* camera, Sampler* sampler, const Bounds2i& pixelBounds);
    ~SamplerIntegrator();
    virtual void preprocess(const Scene* scene) = 0;
    virtual RGBSpectrum Li(const RayDifferential& ray, const Scene* scene, int depth) const = 0;
    void render(const Scene* scene) override;
};

#endif