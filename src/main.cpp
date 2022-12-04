#include <iostream>
#include "mga_problem.h"
#include "genetic.h"


int main(int argc, char *argv[]){

    std::srand(std::time(nullptr));
    // //Voyager 
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
    genOp.elitism_n = 2;
    genOp.selectionType = SELECTION_ROULETTE;
    genOp.crossOverType = CROSS_DOUBLE_POINT;
    genOp.crossOverProb = 0.9;
    genOp.mutationProb = 0.2;

    // Problem definition and times settings
    float Tdep = 2443145.f;
    std::pair<float, float> dep_window = {0.f, 1095.f}; // NOTE: First value (min) should be 0 as it is the departure!
    std::pair<float, float> t1_window = {50.f, 2000.f};
    std::pair<float, float> t2_window = {50.f, 2000.f};

    ProblemDefinition prob = ProblemDefinition(Tdep);
    prob.add_planet(EARTH, dep_window.first, dep_window.second);
    prob.add_planet(JUPITER, t1_window.first, t1_window.second);
    prob.add_planet(SATURN, t2_window.first, t2_window.second);

    // Population and genetic algorithm
    Population population = Population(genOp, &prob);
    population.inception();
    population.runGeneration();
    //population.plotFitnessEvolution();

    MGAProblem mga = MGAProblem(population.population.at(0));
    mga.compute();
    mga.print();
    mga.plot();

    // std::cout << population.population.at(0).flyTimes.at(0) << std::endl;
    // std::cout << population.population.at(0).flyTimes.at(1) << std::endl;
    // std::cout << population.population.at(0).flyTimes.at(2) << std::endl;

    // MGAProblem mga_real = MGAProblem();
    // mga_real.add_planet(EARTH, 2443391);
    // mga_real.add_planet(JUPITER, 2444009);
    // mga_real.add_planet(SATURN, 2444555);
    // mga_real.compute();
    // mga_real.print();
    // mga_real.plot();
    
}