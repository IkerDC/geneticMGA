#ifndef MGA_PROBLEM_H
#define MGA_PROBLEM_H

#include <vector>
#include <string>
#include <iostream>
#include <ostream>

#include "utilities.h"
#include "visualize.h"
#include "planet.h"
#include "transfer.h"
#include "flyby.h"

class MGAProblem{
public:
    std::vector<Planet> planets;
    std::vector<Transfer> transfers;
    std::vector<Flyby> flybys;
    
    MGAProblem();
    ~MGAProblem();

    void add_planet(const int planet, float at);
    void add_planet(const int planet, std::string at);
    void compute_transfers();
    void compute_flybys();

    double computeCost() const;
    bool isSolutionValid() const;

    void plot() const;
    void print() const;
};


#endif //MGA_PROBLEM_H