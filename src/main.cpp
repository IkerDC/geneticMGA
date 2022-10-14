#include <iostream>
#include "mga_problem.h"
#include "genetic.h"


int main(int argc, char *argv[]){
    //Voyager 
    float t1 = 2443389.5;
    float t2 = 2443936.5;
    float t3 = 2444554.5;

    MGAProblem mga = MGAProblem();

    mga.add_planet(EARTH, t1);
    mga.add_planet(JUPITER, t2);
    mga.add_planet(SATURN, t3);

    mga.compute_ephemeris();
    mga.compute_transfers();
    mga.compute_flybys();

    //mga.plot();
    mga.print();

    // Individual from the genetic code testing.

    ProblemDefinition prob = ProblemDefinition();
    prob.add_planet(EARTH, t1, t1 + 1, true);
    prob.add_planet(JUPITER, t2-t1, t2-t1 + 1);
    prob.add_planet(SATURN, t3-t2, t3-t2 + 1);

    Individual ind = Individual(&prob);
    ind.flyTimes.push_back(t1);
    ind.flyTimes.push_back(t2-t1);
    ind.flyTimes.push_back(t3-t2);

    ind.evaluate();

    // Individual ind = Individual(prob); // Reference to prob
    std::srand(std::time(nullptr)); // Init the random time.

}