#include <iostream>
#include "mga_problem.h"
#include "genetic.h"


int main(int argc, char *argv[]){

    std::srand(std::time(nullptr));
    //Voyager 
    // float t1 = 2443389.5;
    // float t2 = 2443936.5;
    // float t3 = 2444554.5;

    // MGAProblem mga = MGAProblem();

    // mga.add_planet(EARTH, t1);
    // mga.add_planet(JUPITER, t2);
    // mga.add_planet(SATURN, t3);

    // mga.compute();

    // //mga.plot();
    // mga.print();

    // Individual from the genetic code testing.
    
    // Genetic operation parameters setting.
    GenOperators genOp;
    genOp.roulette = true;
    genOp.crossOver = 0.9;
    genOp.reproduction = 0.1;
    genOp.elitism = 1;
    genOp.mutation = 0.05;
    genOp.n_tournament = 2;

    // Problem definition and times settings
    std::pair<float, float> dep = {2443145.5, 2444240.5};
    std::pair<float, float> t1 = {50.f, 2000.f};
    std::pair<float, float> t2 = {50.f, 2000.f};

    ProblemDefinition prob = ProblemDefinition();
    prob.add_departure(EARTH, dep.first, dep.second);
    prob.add_planet(JUPITER, t1.first, t1.second);
    prob.add_planet(SATURN, t2.first, t2.second);

    // Population and genetic algorithm
    Population population = Population(genOp, &prob);
    population.inception();
    population.runGeneration();
    
}