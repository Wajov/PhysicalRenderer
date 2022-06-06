cmake_minimum_required(VERSION 3.22)
project(PhysicalRenderer)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
set(HEADER
        src/MathHelper.h
        src/MaterialHelper.h
        src/SampleHelper.h
        src/spectrum/Spectrum.h
        src/spectrum/RGBSpectrum.h
        src/material/BxDF.h
        src/material/Fresnel.h
        src/material/DielectricFresnel.h
        src/material/ConductorFresnel.h
        src/material/SpecularReflection.h
        src/material/SpecularTransmission.h
        src/material/FresnelSpecular.h
        src/material/LambertianReflection.h
        src/material/LambertianTransmission.h
        src/material/OrenNayarReflection.h
        src/material/MicrofacetDistribution.h
        src/material/BeckmannSpizzichinoDistribution.h
        src/material/TrowbridgeReitzDistribution.h
        src/material/MicrofacetReflection.h)
set(SOURCE
        src/main.cpp
        src/spectrum/RGBSpectrum.cpp
        src/material/BxDF.cpp
        src/material/Fresnel.cpp
        src/material/DielectricFresnel.cpp
        src/material/ConductorFresnel.cpp
        src/material/SpecularReflection.cpp
        src/material/SpecularTransmission.cpp
        src/material/FresnelSpecular.cpp
        src/material/LambertianReflection.cpp
        src/material/LambertianTransmission.cpp
        src/material/OrenNayarReflection.cpp
        src/material/MicrofacetDistribution.cpp
        src/material/BeckmannSpizzichinoDistribution.cpp
        src/material/TrowbridgeReitzDistribution.cpp
        src/material/MicrofacetReflection.cpp)
add_executable(PhysicalRenderer
        ${HEADER}
        ${SOURCE})

# Eigen
find_package(Eigen3)
include_directories(${EIGEN3_INCLUDE_DIR})