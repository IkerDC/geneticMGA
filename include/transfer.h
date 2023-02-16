#ifndef TRANSFER_H
#define TRANSFER_H

#include <vector>
#include <string>
#include <iostream>

#include "utilities.h"
#include "planet.h"

class Transfer{
public:
    Planet* p1;         // Reference of departure planet.
    Planet* p2;         // Reference of arrival planet.
    double v_dep[3];    // Departure velocity of the transfer from p1 (computed in compute_transfer by the Lambert solver)
    double v_arr[3];    // Arrival velocity of the transfer at p2 (computed in compute_transfer by the Lambert solver)
    
    Transfer();
    ~Transfer();    

    void add_planets(Planet* p1, Planet* p2);   // Sets p1 and p2.
    void compute_transfer(float T);             // Solves the transfer. Sets v_dep, v_arr.
};

#endif //TRANSFER_H