#include <iostream>
#include "planet.h"


int main(int argc, char *argv[]){
    Planet earth = Planet(EARTH);
    float jd = 2429192.5;
    float x, y, z;
    earth.get_position(jd, x, y, z);
}