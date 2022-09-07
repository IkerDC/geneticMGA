#ifndef FLYBY_H
#define FLYBY_H

#include <vector>
#include <string>
#include <iostream>

#include "transfer.h"

class Flyby{
public:
    Planet* planet;
    Transfer* trans1;
    Transfer* trans2;
    double v_in_rel[3];
    double v_out_rel[3];
    double delta, peri, e, dV;
    
    Flyby();
    ~Flyby();

    void add_planet_transfer(const Planet& p, const Transfer& t1, const Transfer& t2);
    void compute_flyby();
};

#endif //FLYBY_H