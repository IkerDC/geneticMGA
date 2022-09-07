#ifndef TRANSFER_H
#define TRANSFER_H

#include <vector>
#include <string>
#include <iostream>

#include "utilities.h"
#include "planet.h"

class Transfer{
public:
    Planet* p1;
    Planet* p2;
    double v_dep[3];
    double v_arr[3];
    double T;
    
    Transfer();
    ~Transfer();

    void add_planets(const Planet& p1, const Planet& p2);
    void compute_transfer();

    void print() const;
};

#endif //TRANSFER_H