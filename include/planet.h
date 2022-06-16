#ifndef PLANET_H
#define PLANET_H

#include "utilities.h"
#include "astro.h"

class Planet{
private:
    float a0, acy;
    float e0, ecy;
    float I0, Icy;
    float L0, Lcy;
    float long_peri0, lon_pericy;
    float long_node0, long_nodecy;

public:
    Planet(int planet);
    ~Planet();
    void get_position(double t_epoch, float* x, float* y, float *z) const;
    void get_velocity(double t_epoch, float* x, float* y, float *z) const;
};

#endif //PLANET