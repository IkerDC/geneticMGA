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
    genOp.elitism_n = 10;
    genOp.selectionType = SELECTION_ROULETTE;
    genOp.crossOverType = CROSS_DOUBLE_POINT;
    genOp.crossOverProb = 0.9;
    genOp.mutationProb = 0.05;

    // Problem definition and times settings
    int Tdep = 2443145;
    std::pair<int, int> dep_window = {0, 1095}; // NOTE: First value (min) should be 0 as it is the departure!
    std::pair<int, int> t1_window = {50, 2000};
    std::pair<int, int> t2_window = {50, 2000};

    ProblemDefinition prob = ProblemDefinition(Tdep);
    prob.add_planet(EARTH, dep_window.first, dep_window.second);
    prob.add_planet(JUPITER, t1_window.first, t1_window.second);
    prob.add_planet(SATURN, t2_window.first, t2_window.second);

    // Population and genetic algorithm
    Population population = Population(genOp, &prob);
    population.inception();
    population.runGeneration();
    population.plotFitnessEvolution();

    MGAProblem mga = MGAProblem(population.population.at(0)); //FIXME: NOT SURE THIS WORKS RIGHT! SHOULD BE CHECKED!
    mga.compute();
    mga.print();
    mga.plot();

    MGAProblem mga_real = MGAProblem();
    mga_real.add_planet(EARTH, 2443391);
    mga_real.add_planet(JUPITER, 2444009);
    mga_real.add_planet(SATURN, 2444555);
    mga_real.compute();
    mga_real.print();
    mga_real.plot();
    
}