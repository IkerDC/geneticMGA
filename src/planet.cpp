#include "planet.h"

Planet::Planet(int planet, float){
    this->at = at;
    switch (planet)
    {
    case MERCURY:
        this->setParameters(kepler_orbits::mercury, kepler_orbits::mercury_cy, kepler_orbits::mercury_mu);
        break;
    
    case VENUS:
        this->setParameters(kepler_orbits::venus, kepler_orbits::venus_cy, kepler_orbits::venus_mu);
        break;
    
    case EARTH:
        this->setParameters(kepler_orbits::earth, kepler_orbits::earth_cy, kepler_orbits::earth_mu);
        break;

    case MARS:
        this->setParameters(kepler_orbits::mars, kepler_orbits::mars_cy, kepler_orbits::mars_mu);
        break;

    case JUPITER:
        this->setParameters(kepler_orbits::jupiter, kepler_orbits::jupiter_cy, kepler_orbits::jupiter_mu);
        break;

    case SATURN:
        this->setParameters(kepler_orbits::saturn, kepler_orbits::saturn_cy, kepler_orbits::saturn_mu);
        break;

    case URANUS:
        this->setParameters(kepler_orbits::uranus, kepler_orbits::uranus_cy, kepler_orbits::uranus_mu);
        break;

    case NEPTUNE:
        this->setParameters(kepler_orbits::neptune, kepler_orbits::neptune_cy, kepler_orbits::neptune_mu);
        break;

    default:
        throw UnknowPLanet();
        break;
    }
}

Planet::~Planet(){
}

void Planet::setParameters(const float param[6], const float param_cy[6], double mu){
    this->mu = mu;

    // Orbital parametres
    this->a0 = param[0];
    this->acy = param_cy[0];
    this->e0 = param[1];
    this->ecy = param_cy[1];
    this->I0 = param[2];
    this->Icy = param_cy[2];
    this->L0 = param[3];
    this->Lcy = param_cy[3];
    this->long_peri0 = param[4];
    this->long_pericy = param_cy[4];
    this->long_node0 = param[5];
    this->long_nodecy = param_cy[5];
}

void Planet::compute_eph(){

}
