#ifndef CAMERA_SAMPLE_H
#define CAMERA_SAMPLE_H

#include <Eigen/Dense>

class CameraSample {
public:
    Eigen::Vector2f pFilm, pLens;
    float time;
    CameraSample();
    ~CameraSample();
};


#endif