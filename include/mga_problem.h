#ifndef MGA_PROBLEM_H
#define MGA_PROBLEM_H

#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include "nlohmann/json.hpp"

#include "utilities.h"
#include "planet.h"
#include "transfer.h"
#include "flyby.h"
#include "genetic.h"

class MGAProblem{
public:
    std::vector<Planet> planets;    // Sequence of planets in the trajectory (size N)
    std::vector<Transfer> transfers;// Transfer between all the planets.     (size N-1)
    std::vector<Flyby> flybys;      // Flybys                                (size N-2)
    std::vector<float> times;       // Vector of times, i.e input/solution of the trajectory.
    
    MGAProblem();
    MGAProblem(const Individual ind);   // Constructor from and individual. 
    ~MGAProblem();

    void add_planet(const int planet, float at);    // Adds a planet at a given time.
    void compute_ephemeris();                       // Computes ephemeris (planets locations and velocities at their times).
    void compute_transfers();                       // Computes the transfer between planets (velocities needed).
    void compute_flybys();                          // Computes the flybys at the planets.

    void compute();                 // Computes the trajectorty. Ephemeris -> transfer -> flybys. Calls the three function. Completes transfer and flybys attributes in the class.

    void plot() const;      // Plots the solution. Uses the Python code.
    void print() const;     // Prints a description of the whole trajectory.
};


#endif //MGA_PROBLEM_H