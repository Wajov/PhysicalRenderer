#include "Film.h"

Film::Film(const Eigen::Vector2i& resolution, const Bounds2f& cropWindow, Filter* filter, float diagonal, const std::string& filename, float scale, float maxSampleLuminance) :
    resolution(resolution),
    filter(filter),
    diagonal(0.001f * diagonal),
    filename(filename),
    scale(scale),
    maxSampleLuminance(maxSampleLuminance) {
    croppedPixelBounds.pMin = Eigen::Vector2i((int)std::ceil((float)resolution.x() * cropWindow.pMin.x()), (int)std::ceil((float)resolution.y() * cropWindow.pMin.y()));
    croppedPixelBounds.pMin = Eigen::Vector2i((int)std::ceil((float)resolution.x() * cropWindow.pMax.x()), (int)std::ceil((float)resolution.y() * cropWindow.pMax.y()));
    pixels = new Pixel[croppedPixelBounds.area()];

    filterTableWidth = 16;
    filterTable = new float[filterTableWidth * filterTableWidth];
    Eigen::Vector2f filterRadius = filter->getRadius();
    int offset = 0;
    for (int y = 0; y < filterTableWidth; y++)
        for (int x = 0; x < filterTableWidth; x++, offset++) {
            Eigen::Vector2f p;
            p.x() = ((float)x + 0.5f) * filterRadius.x() / (float)filterTableWidth;
            p.y() = ((float)y + 0.5f) * filterRadius.y() / (float)filterTableWidth;
            filterTable[offset] = filter->evaluate(p);
        }
}

Film::~Film() {
    delete[] filterTable;
}

Eigen::Vector2i Film::getResolution() const {
    return resolution;
}

Bounds2i Film::getSampleBounds() const {
    Eigen::Vector2f filterRadius = filter->getRadius();
    Eigen::Vector2i pMin = floor(croppedPixelBounds.pMin.cast<float>() + Eigen::Vector2f(0.5f, 0.5f) - filterRadius);
    Eigen::Vector2i pMax = ceil(croppedPixelBounds.pMax.cast<float>() - Eigen::Vector2f(0.5f, 0.5f) + filterRadius);
    return Bounds2i(pMin, pMax);
}

void Film::addSample(const Eigen::Vector2f& p, const RGBSpectrum& L, float sampleWeight) {
    Spectrum spectrum = L.toXYZ();
    if (spectrum[1] > maxSampleLuminance)
        spectrum *= maxSampleLuminance / spectrum[1];

    Eigen::Vector2f pDiscrete = p - Eigen::Vector2f(0.5f, 0.5f);
    Eigen::Vector2f filterRadius = filter->getRadius();
    Eigen::Vector2i pMin = ceil(pDiscrete - filterRadius);
    Eigen::Vector2i pMax = floor(pDiscrete + filterRadius);
    pMin = croppedPixelBounds.adjust(pMin);
    pMax = croppedPixelBounds.adjust(pMax);

    Eigen::Vector2f invFilterRadius = filter->getInvRadius();
    int *ifx = new int[pMax.x() - pMin.x() + 1];
    for (int x = pMin.x(); x <= pMax.x(); x++) {
        float fx = std::abs(((float)x - pDiscrete.x()) * invFilterRadius.x() * (float)filterTableWidth);
        ifx[x - pMin.x()] = std::min((int)std::floor(fx), filterTableWidth - 1);
    }
    int *ify = new int[pMax.y() - pMin.y() + 1];
    for (int y = pMin.y(); y <= pMax.y(); y++) {
        float fy = std::abs(((float)y - pDiscrete.y()) * invFilterRadius.y() * (float)filterTableWidth);
        ify[y - pMin.y()] = std::min((int)std::floor(fy), filterTableWidth - 1);
    }

    for (int y = pMin.y(); y <= pMax.y(); y++)
        for (int x = pMin.x(); x <= pMax.x(); x++) {
            int filterOffset = ify[y - pMin.y()] * filterTableWidth + ifx[x - pMin.x()];
            float filterWeight = filterTable[filterOffset];

            int pixelOffset = (y - croppedPixelBounds.pMin.y()) * (croppedPixelBounds.pMax.x() - croppedPixelBounds.pMin.x()) + (x - croppedPixelBounds.pMin.x());
            pixels[pixelOffset].spectrumSum += filterWeight * sampleWeight * spectrum;
            pixels[pixelOffset].filterWeightSum += filterWeight;
        }

    delete[] ifx;
    delete[] ify;
}
