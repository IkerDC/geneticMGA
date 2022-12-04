#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <cmath>
#include <string>

#include "astro.h"
#include "my_exceptions.h"
#include "orbital_mechanics.h"

class Planet{
public:
    std::string name;
    orbitalParameters prm;
    double mu;
    double k_rad;  //safe radius factor
    float at;
    double r_eph[3];
    double v_eph[3];

    Planet();
    Planet(int planet);
    ~Planet();
    
    void setParameters(const float param[6], const float param_cy[6], const double mu, const double k);
    void compute_eph(float at);
};

#endif //PLANET