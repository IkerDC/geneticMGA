#include "planet.h"

Planet::Planet(){

}

Planet::Planet(int planet){
    
    switch (planet)
    {
    case MERCURY:
        this->name = "mercury";
        this->setParameters(kepler_orbits::mercury, kepler_orbits::mercury_cy, kepler_orbits::mercury_mu);
        break;
    
    case VENUS:
        this->name = "venus";
        this->setParameters(kepler_orbits::venus, kepler_orbits::venus_cy, kepler_orbits::venus_mu);
        break;
    
    case EARTH:
        this->name = "earth";
        this->setParameters(kepler_orbits::earth, kepler_orbits::earth_cy, kepler_orbits::earth_mu);
        break;

    case MARS:
        this->name = "mars";
        this->setParameters(kepler_orbits::mars, kepler_orbits::mars_cy, kepler_orbits::mars_mu);
        break;

    case JUPITER:
        this->name = "jupiter";
        this->setParameters(kepler_orbits::jupiter, kepler_orbits::jupiter_cy, kepler_orbits::jupiter_mu);
        break;

    case SATURN:
        this->name = "saturn";
        this->setParameters(kepler_orbits::saturn, kepler_orbits::saturn_cy, kepler_orbits::saturn_mu);
        break;

    case URANUS:
        this->name = "uranus";
        this->setParameters(kepler_orbits::uranus, kepler_orbits::uranus_cy, kepler_orbits::uranus_mu);
        break;

    case NEPTUNE:
        this->name = "neptune";
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
    this->prm.a0 = param[0];
    this->prm.acy = param_cy[0];
    this->prm.e0 = param[1];
    this->prm.ecy = param_cy[1];
    this->prm.I0 = param[2];
    this->prm.Icy = param_cy[2];
    this->prm.L0 = param[3];
    this->prm.Lcy = param_cy[3];
    this->prm.long_peri0 = param[4];
    this->prm.long_pericy = param_cy[4];
    this->prm.long_node0 = param[5];
    this->prm.long_nodecy = param_cy[5];
}

void Planet::compute_eph(float at){
    /**
     * @brief Utilizes the ephemris function to set compute the ephemeris a the predifined date set in the class.
     */
    orbit::ephemeris(this->prm, at, this->r_eph, this->v_eph);
}
