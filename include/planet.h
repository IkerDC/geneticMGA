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
    float at;
    double r_eph[3];
    double v_eph[3];

    Planet(int planet, float at);
    ~Planet();
    
    void setParameters(const float param[6], const float param_cy[6], double mu);
    void compute_eph();
};

#endif //PLANET