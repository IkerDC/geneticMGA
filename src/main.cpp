#include <iostream>
#include "mga_problem.h"


int main(int argc, char *argv[]){
    // Testing the MGA class
    float t1 = 2447848.5;
    float t2 = 2447945.5;
    float t3 = 2448218.5;
    float t4 = 2448944.5;

    MGAProblem mga = MGAProblem();

    mga.add_planet(EARTH, t1);
    mga.add_planet(VENUS, t2);
    mga.add_planet(EARTH, t3);
    mga.add_planet(EARTH, t4);
    
    mga.compute_ephemeris();
    mga.compute_transfers();
    mga.compute_flybys();

    std::cout << "\n **************** \n" << std::endl;

    // SIMULATE VOYAGER
    Planet earth = Planet(EARTH, t1);
    Planet venus = Planet(VENUS, t2);
    Planet earth_2 = Planet(EARTH, t3);
    Planet earth_3 = Planet(EARTH, t4);

    double r_earth[3], v_earth[3], v_dep_earth[3], v_arr_earth[3];
    double r_earth_2[3], v_earth_2[3], v_dep_earth_2[3], v_arr_earth_2[3];
    double r_earth_3[3], v_earth_3[3], v_dep_earth_3[3], v_arr_earth_3[3];
    double r_venus[3], v_venus[3], v_dep_venus[3], v_arr_venus[3];

    float dt1 = (t2-t1)*DAY2SEC;
    float dt2 = (t3-t2)*DAY2SEC;
    float dt3 = (t4-t3)*DAY2SEC;

    orbit::ephemeris(earth.prm, t1, r_earth, v_earth);
    orbit::ephemeris(venus.prm, t2, r_venus, v_venus);
    orbit::ephemeris(earth.prm, t3, r_earth_2, v_earth_2);
    orbit::ephemeris(earth.prm, t4, r_earth_3, v_earth_3);

    orbit::lambert(r_earth, r_venus, dt1, MU_SUN, v_dep_earth, v_arr_venus);
    orbit::lambert(r_venus, r_earth_2, dt2, MU_SUN, v_dep_venus, v_arr_earth_2);
    orbit::lambert(r_earth_2, r_earth_3, dt3, MU_SUN, v_dep_earth_2, v_arr_earth_3);

    double dV, dV2, delta, peri;
    orbit::patched_conic(v_arr_venus, v_dep_venus, v_venus, venus.mu, dV, delta, peri);
    orbit::patched_conic(v_arr_earth_2, v_dep_earth_2, v_earth_2, earth.mu, dV, delta, peri);
}