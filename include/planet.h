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
    std::string name;       // Name of planet
    orbitalParameters prm;  // orbital elements of the planet
    double mu;              // gravitational const of the planet
    double rad;             // radius of the planet
    double mass;            // mass of planet
    double sun_dist;        // distance of the planet to the Sun
    double r_eph[3];        // position of planet at its time. Ephemeris R 
    double v_eph[3];        // velocity of planet at its time. Ephemeris V

    Planet();
    Planet(int planet);     
    ~Planet();
    
    void setParameters(const float param[6], const float param_cy[6], planet_props::Properties props);  // Sets prm.
    void compute_eph(float at);     // Computes ephemeris. Sets r_eph and v_eph at time "at" in JD format as always. 
    void Planet_Ephemerides_Analytical(const double &, const int &);  //Pykep implementation of the ephemeris (is more precise than compute_eph, but should do the same)   
};

#endif //PLANET