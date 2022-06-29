#include <iostream>
#include "planet.h"
#include "pagmo/Lambert.h"


int main(int argc, char *argv[]){
    Planet earth = Planet(EARTH);
    Planet mars = Planet(MARS);
    float departure = 2451544.5;
    float arrival = 2452184.5;
    double r_e[3];
    double v_dep[3];
    double r_m[3];
    double v_arr[3];
    float T = 55296000.0;
    int lw = 0;
    earth.get_position(departure, r_e);
    mars.get_position(arrival, r_m);
    double a, p, theta;
    int iter;
    LambertI(r_e, r_m, T, MU_SUN, lw, v_dep, v_arr, a, p, theta, iter);
    std::cout << "Position from earth" << std::endl;
    for(unsigned int i = 0; i <3; i++){
        std::cout << r_e[i] << std::endl; 
    }
    std::cout << "Position from mars" << std::endl;
    for(unsigned int i = 0; i <3; i++){
        std::cout << r_m[i] << std::endl; 
    }
    std::cout << "Speed from earth" << std::endl;
    for(unsigned int i = 0; i <3; i++){
        std::cout << v_dep[i] << std::endl; 
    }
    std::cout << "Speed from mars" << std::endl;
    for(unsigned int i = 0; i <3; i++){
        std::cout << v_arr[i] << std::endl; 
    }

}