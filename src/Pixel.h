#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
public:
    float filterWeightSum, xyz[3], splatXYZ[3];
    Pixel();
    ~Pixel();
};

#endif