#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Scene.h"

class Integrator {
public:
    Integrator();
    ~Integrator();
    virtual void render(const Scene& scene) = 0;
};

#endif