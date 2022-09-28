#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <iostream>
#include <string>
#include <random>

#include "planet.h"
#include "my_exceptions.h"

class ProblemDefinition {
public:
    Planet departurePlanet;
    std::pair<int, int> departureWindow;
    
    std::vector<Planet> flybyPlanets;
    std::vector<std::pair<int, int>> flybyWindows;

    ProblemDefinition();
    ~ProblemDefinition();

    void add_departure(int _p, int min, int max);
    void add_flyby(int _p, int min, int max); 
};


class Individual {
public:
    const ProblemDefinition* problem;
    std::vector<int> flyTimes;
    float fitness;
    float cost;

    Individual(ProblemDefinition& prob);
    ~Individual();
    
    void init();
    int times2bit() const;
    float getFlyTime() const;

    void evaluate();
};

#endif //INDIVIDUAL_H