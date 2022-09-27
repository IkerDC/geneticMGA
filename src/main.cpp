#include <iostream>
#include "mga_problem.h"


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

    mga.plot();
    mga.print();

}