#include <iostream>
#include "planet.h"
#include "flyby.h"
#include "pagmo/Lambert.h"


int main(int argc, char *argv[]){
    Planet earth = Planet(EARTH);
    Planet mars = Planet(MARS);
    Planet jupiter = Planet(JUPITER);

    float t1 = 2451544.5;
    float t2 = 2452184.5;
    float t3 = 2453984.5;

    double r_earth[3], v_earth[3], v_dep_earth[3], v_arr_earth[3];
    double r_mars[3], v_mars[3], v_dep_mars[3], v_arr_mars[3];
    double r_jupiter[3], v_jupiter[3], v_dep_jupiter[3], v_arr_jupiter[3];

    float dt1 = (t2-t1)*DAY2SEC;
    float dt2 = (t3-t2)*DAY2SEC;

    int lw = 1; // long way, i.e. less dv
    earth.get_ephemeris(t1, r_earth, v_earth);
    mars.get_ephemeris(t2, r_mars, v_mars);
    jupiter.get_ephemeris(t3, r_jupiter, v_jupiter);

    double a, p, theta;
    int iter;
    LambertI(r_earth, r_mars, dt1, MU_SUN, lw, v_dep_earth, v_arr_mars, a, p, theta, iter);
    LambertI(r_mars, r_jupiter, dt2, MU_SUN, lw, v_dep_mars, v_arr_jupiter, a, p, theta, iter);
    
    std::cout << "Mars arriving speed from lambert" << std::endl;
    for(unsigned int i = 0; i < 3; i++){
        std::cout<< v_arr_mars[i] << std::endl;
    }
    std::cout << "Mars departure speed from lambert" << std::endl;
    for(unsigned int i = 0; i < 3; i++){
        std::cout<< v_dep_mars[i] << std::endl;
    }
    
    // Now lets patch this togheter
    FlyBy flybyMG = FlyBy(&mars, dt1);
    flybyMG.set_planet_v(v_mars);
    flybyMG.set_incoming_v(v_arr_mars);
    flybyMG.set_outgoing_v(v_dep_mars);
    flybyMG.compute_flyby();
    
    // std::cout << " **** Flyby info: " << std::endl;
    // std::cout << "Periphasis r: "<< flybyMG.get_periphasis() << std::endl;
    // double dv[3];
    // flybyMG.get_deltaV(dv);
    // for(unsigned int i = 0; i < 3;i++){
    //     std::cout << dv[i] << std::endl;
    // }
}