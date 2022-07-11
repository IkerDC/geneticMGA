#include "planet.h"

Planet::Planet(int planet){
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

void Planet::get_ephemeris(double T_eph, double* r, double* v) const{
    /**
    * @brief Get position of planet on the orbit on a given JD date.
    * Epoch: Double representing the JD
    * x : Store variable for x pos
    * y : Store variable for y pos
    * z : Store variable for z pos
    */

    double T_pastCenJ2000 = (T_eph - 2451545.0)/36525;

    // Orbital elements
    double a = this->a0 + this->acy * T_pastCenJ2000;
    double e = this->e0 + this->ecy * T_pastCenJ2000;
    double i = this->I0 + this->Icy * T_pastCenJ2000;
    double L = this->L0 + this->Lcy * T_pastCenJ2000;
    double p = this->long_peri0 + this->long_nodecy * T_pastCenJ2000;
    double W = this->long_node0 + this->long_nodecy * T_pastCenJ2000;

    // Convert angles to radians
    i *= PI/180.0;
    L *= PI/180.0;
    p *= PI/180.0;
    W *= PI/180.0;

    double M = L - p; // mean anomaly
    double w = p - W; // 
    
    // Newton-Raphson in order to get the eccentricity
    double E = M;
    double dE = 0.0;
    unsigned int iter = 0;
    while (true){
        dE = (E - e * std::sin(E) - M)/(1 - e * std::cos(E));
        E -= dE;
        if(std::abs(dE) < 1e-6){
            break;
        }
        if(iter > 10000){
            std::cout << "Iteration limit hit on N-R eccenticity anomaly computation." << std::endl;
            break;
        }
        iter++;
    }

    // P, Q 2d coordinate system - Position
    double P = a * (std::cos(E) - e);
    double Q = a * std::sin(E) * std::sqrt(1 - std::pow(e, 2));

    // P, Q 2d coordinate system - Velocity
    double vP = - (a * std::sin(E) * this->Lcy) / (1 - e * std::cos(E));
    double vQ = (a * std::cos(E) * std::sqrt(1 - e*e) * this->Lcy) / (1 - e * std::cos(E));

    rotate_eph(w, W, i, P, Q, r); 
    rotate_eph(w, W, i, vP, vQ, v);
    
    // Save in the output
    r[0] *= UA;
    r[1] *= UA;
    r[2] *= UA;

    v[0] *= CORRECTION;
    v[1] *= CORRECTION;
    v[2] *= CORRECTION;
}
