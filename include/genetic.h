#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <bits/stdc++.h>

#include "planet.h"
#include "my_exceptions.h"
#include "utilities.h"


#define N_POPULATION 5000

struct GenOperators{
    float crossOver;
    float reproduction;
    float mutation;  
    int elitism;
    int n_tournament = 2;
    bool roulette;
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
    ProblemDefinition* problem;         // Problem reference (planets reference to operate are in there).
    float fitness;                      // Fitness of the individual.
    float cost;                         // Total cost of the individual based on the cost function.

    Individual();
    Individual(ProblemDefinition& prob);
    ~Individual();
    
    Individual mate(const Individual& partner); // Mate with another individual to create a new child.
    void createMutation();

    void init();
    int times2bit() const;
    float getFlyTime() const;

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

    Population(const GenOperators params, ProblemDefinition& problem);
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