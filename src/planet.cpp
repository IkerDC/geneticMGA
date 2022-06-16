#include "planet.h"

Planet::Planet(int planet){
    switch (planet)
    {
    case MERCURY:
        /* code */
        break;
    
    case VENUS:
        /* code */
        break;
    
    case EARTH:
        /* code */
        break;

    case MARS:
        /* code */
        break;

    case JUPITER:
        /* code */
        break;

    case SATURN:
        /* code */
        break;

    case URANUS:
        /* code */
        break;

    case NEPTUNE:
        /* code */
        break;

    default:
        break;
    }
}

Planet::~Planet(){
}

void Planet::get_position(double t_epoch, float* x, float* y, float *z) const{
    
}

void Planet::get_velocity(double t_epoch, float* x, float* y, float *z) const{

}