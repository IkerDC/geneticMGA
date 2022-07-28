#include <iostream>
#include "planet.h"
#include "flyby.h"
#include "pagmo/Lambert.h"


int main(int argc, char *argv[]){
    // SIMULATE VOYAGER
    Planet earth = Planet(EARTH);
    Planet jupiter = Planet(JUPITER);
    Planet saturn = Planet(SATURN);

    float t1 = 2443390.1;
    float t2 = 2444008.393;
    float t3 = 2444555.026;

    double r_earth[3], v_earth[3], v_dep_earth[3], v_arr_earth[3];
    double r_jupiter[3], v_jupiter[3], v_dep_jupiter[3], v_arr_jupiter[3];
    double r_saturn[3], v_saturn[3], v_dep_saturn[3], v_arr_saturn[3];

    float dt1 = (t2-t1)*DAY2SEC;
    float dt2 = (t3-t2)*DAY2SEC;

    int lw = 0; // long way, i.e. less dv
    earth.get_ephemeris(t1, r_earth, v_earth);
    jupiter.get_ephemeris(t2, r_jupiter, v_jupiter);
    saturn.get_ephemeris(t3, r_saturn, v_saturn);

    double a, p, theta;
    int iter;
    double rE[3] = {142894308003.52066, -48428290555.142769, -2430283.7650731262};
    double rJ[3] = {-543656481505.61536, 579793743395.7583, 9786902396.7249565};
    double rS[3] = {-1419710545425.1218, -53519710277.703804, 57358162162.15981};

    LambertI(rE, rJ, dt1, MU_SUN, lw, v_dep_earth, v_arr_jupiter, a, p, theta, iter);
    LambertI(r_jupiter, r_saturn, dt2, MU_SUN, lw, v_dep_jupiter, v_arr_saturn, a, p, theta, iter);
    
    std::cout << "Jupiter arriving speed from lambert" << std::endl;
    for(unsigned int i = 0; i < 3; i++){
        std::cout<< v_arr_jupiter[i] << std::endl;
    }
    std::cout << "Jupiter departure speed from lambert" << std::endl;
    for(unsigned int i = 0; i < 3; i++){
        std::cout<< v_dep_jupiter[i] << std::endl;
    }
    
    // Now lets patch this togheter
    FlyBy flybyMG = FlyBy(&jupiter, dt1);
    flybyMG.set_planet_v(v_jupiter);
    flybyMG.set_incoming_v(v_arr_jupiter);
    flybyMG.set_outgoing_v(v_dep_jupiter);
    flybyMG.compute_flyby();
    
    // std::cout << " **** Flyby info: " << std::endl;
    // std::cout << "Periphasis r: "<< flybyMG.get_periphasis() << std::endl;
    // double dv[3];
    // flybyMG.get_deltaV(dv);
    // for(unsigned int i = 0; i < 3;i++){
    //     std::cout << dv[i] << std::endl;
    // }
}