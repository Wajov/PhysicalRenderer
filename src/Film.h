#ifndef FILM_H
#define FILM_H

#include <Eigen/Dense>
#include <cstring>

#include "MathHelper.h"
#include "Bounds.h"
#include "Pixel.h"
#include "filter/Filter.h"
#include "spectrum/RGBSpectrum.h"

class Film {
private:
    Eigen::Vector2i resolution;
    Bounds2i croppedPixelBounds;
    float diagonal, scale, maxSampleLuminance;
    Filter* filter;
    int filterTableWidth;
    float* filterTable;
    Pixel* pixels;
    std::string filename;

public:
    Film(const Eigen::Vector2i& resolution, const Bounds2f& cropWindow, Filter* filter, float diagonal, const std::string& filename, float scale, float maxSampleLuminance = std::numeric_limits<float>::infinity());
    ~Film();
    Eigen::Vector2i getResolution() const;
    Bounds2i getSampleBounds() const;
    void addSample(const Eigen::Vector2f& p, const RGBSpectrum& L, float sampleWeight = 1.0f);
};

#endif