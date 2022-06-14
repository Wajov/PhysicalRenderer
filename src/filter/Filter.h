#ifndef FILTER_H
#define FILTER_H

#include <Eigen/Dense>

class Filter {
protected:
    Eigen::Vector2f radius, invRadius;

public:
    Filter(const Eigen::Vector2f& radius);
    ~Filter();
    virtual float evaluate(const Eigen::Vector2f& p) const = 0;
};

#endif