#include <iostream>
#include "mga_problem.h"


int main(int argc, char *argv[]){
    // Gallileo real
    float t1 = 2447817.5; //2447848.5;  //-> The ge fake dates
    float t2 = 2447932.5; //2447945.5; 
    float t3 = 2448233.5; //2448218.5;
    float t4 = 2448964.5; //2448944.5;
    float t5 = 2450058.5; //2450034.5;
    
    // Fake dates
    // float t1 = 2447848.5;
    // float t2 = 2447945.5;
    // float t3 = 2448218.5;
    // float t4 = 2448944.5;
    // float t5 = 2450034.5;

    MGAProblem mga = MGAProblem();

    mga.add_planet(EARTH, t1);
    mga.add_planet(VENUS, t2);
    mga.add_planet(EARTH, t3);
    mga.add_planet(EARTH, t4);
    mga.add_planet(JUPITER, t5);

    //Voyager 
    // float t1 = 2443389.5;
    // float t2 = 2443936.5;
    // float t3 = 2444554.5;

    //MGAProblem mga = MGAProblem();

    // mga.add_planet(EARTH, t1);
    // mga.add_planet(VENUS, t2);
    // mga.add_planet(EARTH, t3);
    // mga.add_planet(EARTH, t4);
    // mga.add_planet(JUPITER, t5);

    mga.compute_ephemeris();
    mga.compute_transfers();
    mga.compute_flybys();

    mga.plot();
    mga.print();


    // SIMULATE VOYAGER
    // Planet earth = Planet(EARTH, t1);
    // Planet jupiter = Planet(JUPITER, t2);
    // Planet saturn = Planet(SATURN, t3);
    
    // double r_earth[3], v_earth[3], v_dep_earth[3], v_arr_earth[3];
    // double r_jupiter[3], v_jupiter[3], v_dep_jupiter[3], v_arr_jupiter[3];
    // double r_saturn[3], v_saturn[3], v_dep_saturn[3], v_arr_saturn[3];

    // float dt1 = (t2-t1)*DAY2SEC;
    // float dt2 = (t3-t2)*DAY2SEC;


    // orbit::ephemeris(earth.prm, t1, r_earth, v_earth);
    // orbit::ephemeris(jupiter.prm, t2, r_jupiter, v_jupiter);
    // orbit::ephemeris(saturn.prm, t3, r_saturn, v_saturn);

    // orbit::lambert(r_earth, r_jupiter, dt1, MU_SUN, v_dep_earth, v_arr_jupiter);
    // orbit::lambert(r_jupiter, r_saturn, dt2, MU_SUN, v_dep_jupiter, v_arr_saturn);

    // double dV, delta, peri;
    // double rel_in[3], rel_out[3];
    // orbit::patched_conic(v_arr_jupiter, v_dep_jupiter, v_jupiter, jupiter.mu, dV, delta, peri);
    // minus2(v_arr_jupiter, v_jupiter, rel_in);
    // minus2(v_dep_jupiter, v_jupiter, rel_out);
    // std::cout << "....................................." << std::endl;
    // std::cout << "  Incoming velocity (relative): " << norm(rel_in) << " m/s" << std::endl;
    // std::cout << "  Outgoing velocity (relative): " << norm(rel_out) << " m/s" << std::endl;
    // std::cout << "  Turning angle: " << rad2deg(delta) << "º"<< std::endl;
    // std::cout << "  Periapsis rad: " << peri << " m"<< std::endl;
    // std::cout << "  Total dV     : " << dV << " m/s"<< std::endl;

}