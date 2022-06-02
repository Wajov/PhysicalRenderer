#include "ConductorFresnel.h"

ConductorFresnel::ConductorFresnel(const RGBSpectrum& etaI, const RGBSpectrum& etaT, const RGBSpectrum& k) :
    Fresnel(),
    etaI(etaI),
    etaT(etaT),
    k(k) {}

ConductorFresnel::~ConductorFresnel() {}

RGBSpectrum ConductorFresnel::evaluate(float cosThetaI) const {
    return conductorFresnel(etaI, etaT, k, cosThetaI);
}