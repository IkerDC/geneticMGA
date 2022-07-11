#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <cmath>

#include "utilities.h"
#include "astro.h"
#include "my_exceptions.h"

class Planet{
private:
    float a0, acy; // semi-major axis
    float e0, ecy; // eccentricity
    float I0, Icy; // inlcinations
    float L0, Lcy; // mean longitude
    float long_peri0, long_pericy; // longitude of preiphasis
    float long_node0, long_nodecy; // acending node lingitude

public:
    double mu;
    Planet(int planet);
    ~Planet();
    void setParameters(const float param[6], const float param_cy[6], double mu);
    void get_ephemeris(double T_eph, double* r, double* v) const;
};

#endif //PLANET