#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <bitset>
#include <bits/stdc++.h> // for std::sort

#include "planet.h"
#include "my_exceptions.h"
#include "utilities.h"
#include "orbital_mechanics.h"
#include "numeric"

#define N_POPULATION 5
#define GEN_LIMIT 5

#define SELECTION_ROULETTE      0
#define SELECTION_TOURNAMENT    1

#define TOURNAMENT_N    2

#define CROSS_UNIFORM       0
#define CROSS_SINGLE_GENE   1
#define CROSS_SINGLE_POINT  2
#define CROSS_DOUBLE_POINT  3

struct GenOperators{
    int elitism_n;
    int selectionType;
    int crossOverType;
    float crossOverProb;
    float mutationProb;  
};


class ProblemDefinition {
public:
    int departure;
    std::vector<Planet> planets;
    std::vector<std::pair<int, int>> timeWindows; //{Td(min, max), T1(min,max), T2(min, max), ... }

    ProblemDefinition(const int _dep);
    ~ProblemDefinition();

    void add_planet(int _p, int min, int max);
};


class Individual {
private:
    void updateDepartureCost(double dV);
    void updateCost(const Planet& planet, double dV, double delta, double peri);

public:
    std::vector<int> flyTimes;          // Chromosome (each variable is a gene).
    ProblemDefinition* problem;         // Problem reference (planets reference to operate are in there).
    float fitness;                      // Fitness of the individual.
    float cost;                         // Total cost of the individual based on the cost function.

    Individual();
    Individual(ProblemDefinition* prob);
    ~Individual();
    
    Individual mate(const Individual& partner, int crossType); // Mate with another individual to create a new child.
    void createMutation();

    void init();
    int getFlyTime() const;

    void evaluate();

    // Used to facilitate sorting of individuals.
    bool operator< (const Individual &other) const {
        return fitness < other.fitness;
    }
};


class Population{
private:
    void sortPopulation();

public:
    std::vector<Individual> population;
    std::vector<Individual> newPopulation;
    const GenOperators geParameters;
    int generationCount;

    Population(const GenOperators params, ProblemDefinition* problem);
    ~Population();

    void inception();   // let the civilization begin.

    // Genetic operators.
    void selection();
    void crossOver();
    void mutate();
    void elitism();

    void evolveNewGeneration();
    void runGeneration();
};

#endif //INDIVIDUAL_H