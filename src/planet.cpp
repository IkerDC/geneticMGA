#include "planet.h"

Planet::Planet(){

}

Planet::Planet(int planet){
    
    switch (planet)
    {
    case MERCURY:
        this->name = "mercury";
        this->setParameters(kepler_orbits::mercury, kepler_orbits::mercury_cy, planet_props::mercury_mu, planet_props::mercury_k);
        break;
    
    case VENUS:
        this->name = "venus";
        this->setParameters(kepler_orbits::venus, kepler_orbits::venus_cy, planet_props::venus_mu, planet_props::venus_k);
        break;
    
    case EARTH:
        this->name = "earth";
        this->setParameters(kepler_orbits::earth, kepler_orbits::earth_cy, planet_props::earth_mu, planet_props::earth_k);
        break;

    case MARS:
        this->name = "mars";
        this->setParameters(kepler_orbits::mars, kepler_orbits::mars_cy, planet_props::mars_mu, planet_props::mars_k);
        break;

    case JUPITER:
        this->name = "jupiter";
        this->setParameters(kepler_orbits::jupiter, kepler_orbits::jupiter_cy, planet_props::jupiter_mu, planet_props::jupiter_k);
        break;

    case SATURN:
        this->name = "saturn";
        this->setParameters(kepler_orbits::saturn, kepler_orbits::saturn_cy, planet_props::saturn_mu, planet_props::saturn_k);
        break;

    case URANUS:
        this->name = "uranus";
        this->setParameters(kepler_orbits::uranus, kepler_orbits::uranus_cy, planet_props::uranus_mu, planet_props::uranus_k);
        break;

    case NEPTUNE:
        this->name = "neptune";
        this->setParameters(kepler_orbits::neptune, kepler_orbits::neptune_cy, planet_props::neptune_mu, planet_props::neptune_k);
        break;

    default:
        throw UnknowPLanet();
        break;
    }
}

Planet::~Planet(){

}

void Planet::setParameters(const float param[6], const float param_cy[6], const double mu, const double k){
    this->mu = mu;
    this->k_rad = k;

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
