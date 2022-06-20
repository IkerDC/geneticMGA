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
    
    Planet(int planet);
    ~Planet();
    void setParameters(const float param[6], const float param_cy[6]);
    void get_position(double T_eph, float &x, float &y, float &z) const;
    void get_velocity(double T_eph, float &x, float &y, float &z) const;
};

#endif //PLANET