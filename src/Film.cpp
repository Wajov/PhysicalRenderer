#include "Film.h"

Film::Film(const Eigen::Vector2i& resolution, const Bounds2f& cropWindow, Filter* filter, float diagonal, const std::string& filename, float scale, float maxSampleLuminance) :
    resolution(resolution),
    filter(filter),
    diagonal(0.001f * diagonal),
    filename(filename),
    scale(scale),
    maxSampleLuminance(maxSampleLuminance) {
    croppedPixelBounds.pMin = Eigen::Vector2i(std::ceil((float)resolution.x() * cropWindow.pMin.x()), std::ceil((float)resolution.y() * cropWindow.pMin.y()));
    croppedPixelBounds.pMin = Eigen::Vector2i(std::ceil((float)resolution.x() * cropWindow.pMax.x()), std::ceil((float)resolution.y() * cropWindow.pMax.y()));
    pixels = new Pixel[croppedPixelBounds.area()];
}

Film::~Film() {}
