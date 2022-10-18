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
#include "orbital_mechanics.h"
#include "numeric"

#define N_POPULATION 5

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
    std::pair<float, float> departureWindow;
    std::vector<Planet> planets;
    std::vector<std::pair<float, float>> flybyWindows;

    ProblemDefinition();
    ~ProblemDefinition();

    void add_planet(int _p, float min, float max, bool dep = false); 
};


class Individual {
private:
    void updateDepartureCost(double dV);
    void updateCost(const Planet& planet, double dV, double delta, double peri);

public:
    std::vector<float> flyTimes;          // Chromosome (each variable is a gene).
    ProblemDefinition* problem;         // Problem reference (planets reference to operate are in there).
    float fitness;                      // Fitness of the individual.
    float cost;                         // Total cost of the individual based on the cost function.

    Individual();
    Individual(ProblemDefinition* prob);
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