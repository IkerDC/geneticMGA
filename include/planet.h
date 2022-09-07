#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <cmath>

#include "astro.h"
#include "my_exceptions.h"

class Planet{
public:
    float a0, acy; // semi-major axis
    float e0, ecy; // eccentricity
    float I0, Icy; // inlcinations
    float L0, Lcy; // mean longitude
    float long_peri0, long_pericy; // longitude of preiphasis
    float long_node0, long_nodecy; // acending node lingitude
    double mu;

    float at;
    double position[3];

    Planet(int planet, float at);
    ~Planet();
    
    void setParameters(const float param[6], const float param_cy[6], double mu);
    void compute_eph();
};

#endif //PLANET