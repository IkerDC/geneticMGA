#ifndef FLYBY_H
#define FLYBY_H

#include <vector>
#include <string>
#include <iostream>

#include "transfer.h"
#include "planet.h"

class Flyby{
public:
    Planet* planet;     // Reference of the planet where the flyby is being performed.
    Transfer* trans1;   // Reference of arriving transfer (for v_arr of that transfer)
    Transfer* trans2;   // Reference of departing transfer (for v_dep of that transfer)
    double v_in_rel[3]; // Relative to planet incoming velocity of spacecraft 
    double v_out_rel[3];// Relative to planet outfgoing velocity of spacecraft 
    double delta, peri, dV; // delta: turing angle, peri: perigee, dV: delta-v of flyby (to patch the two solutions)
    
    Flyby();
    ~Flyby();

    void add_planet_transfer(Transfer* t1, Transfer* t2);   // Sets the references of the tranfers.
    void compute_flyby();                                   // Computes the flyby.            
    void print() const;                                     // Pretty prints the flyby info.
};

#endif //FLYBY_H