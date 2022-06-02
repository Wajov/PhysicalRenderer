#ifndef SAMPLE_HELPER_H
#define SAMPLE_HELPER_H

#include <cmath>

#include <Eigen/Dense>

inline static Eigen::Vector2f concentricSampleDisk(const Eigen::Vector2f& u) {
    Eigen::Vector2f uOffset = 2.0f * u - Eigen::Vector2f(1.0f, 1.0f);

    if (uOffset == Eigen::Vector2f::Zero())
        return Eigen::Vector2f::Zero();

    float r, theta;
    if (std::abs(uOffset.x()) > std::abs(uOffset.y())) {
        r = uOffset.x();
        theta = PI_OVER_4 * (uOffset.y() / uOffset.x());
    } else {
        r = uOffset.y();
        theta = PI_OVER_2 - PI_OVER_4 * (uOffset.x() / uOffset.y());
    }
    return r * Eigen::Vector2f(std::cos(theta), std::sin(theta));
}

inline static Eigen::Vector3f cosineSampleHemisphere(const Eigen::Vector2f& u) {
    Eigen::Vector2f d = concentricSampleDisk(u);
    float z = std::sqrt(std::max(0.0f, 1.0f - d.squaredNorm()));
    return Eigen::Vector3f(d.x(), d.y(), z);
}

#endif