#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <iostream>
#include <string>
#include <random>

#include "planet.h"
#include "my_exceptions.h"


#define N_POPULATION 5000


struct GenOperators{
    float crossOver;
    float reproduction;
    float mutation;  
    int elitism;
};


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
    std::vector<int> flyTimes;          // Chromosome (each variable is a gene).
    const ProblemDefinition* problem;   // Problem reference (planets reference to operate are in there).
    float fitness;                      // Fitness of the individual.
    float cost;                         // Total cost of the individual based on the cost function.

    Individual(ProblemDefinition& prob);
    ~Individual();
    
    void init();
    int times2bit() const;
    float getFlyTime() const;

    void evaluate();
};

class Population{
public:
    std::vector<Individual> population[N_POPULATION];
    const GenOperators geParameters;
    int generationCount;

    Population(const GenOperators params);
    ~Population();

    void inception();   // let the civilization begin.

    // Genetic operators.
    void crossOver();
    void mutate();
    void elitism();

    void evolverNewGeneration();
    void runGeneration();
};

#endif //INDIVIDUAL_H