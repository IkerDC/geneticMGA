#include "planet.h"

Planet::Planet(int planet){
    switch (planet)
    {
    case MERCURY:
        this->setParameters(kepler_orbits::mercury, kepler_orbits::mercury_cy);
        break;
    
    case VENUS:
        this->setParameters(kepler_orbits::venus, kepler_orbits::venus_cy);
        break;
    
    case EARTH:
        this->setParameters(kepler_orbits::earth, kepler_orbits::earth_cy);
        break;

    case MARS:
        this->setParameters(kepler_orbits::mars, kepler_orbits::mars_cy);
        break;

    case JUPITER:
        this->setParameters(kepler_orbits::jupiter, kepler_orbits::jupiter_cy);
        break;

    case SATURN:
        this->setParameters(kepler_orbits::saturn, kepler_orbits::saturn_cy);
        break;

    case URANUS:
        this->setParameters(kepler_orbits::uranus, kepler_orbits::uranus_cy);
        break;

    case NEPTUNE:
        this->setParameters(kepler_orbits::neptune, kepler_orbits::neptune_cy);
        break;

    default:
        throw UnknowPLanet();
        break;
    }
}

Planet::~Planet(){
}

void Planet::setParameters(const float param[6], const float param_cy[6]){
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

void Planet::get_position(double T_eph, double* r) const{
    /**
    * @brief Get position of planet on the orbit on a given JD date.
    * Epoch: Double representing the JD
    * x : Store variable for x pos
    * y : Store variable for y pos
    * z : Store variable for z pos
    */

    float T_pastCenJ2000 = (T_eph - 2451545.0)/36525;

    // Orbital elements
    float a = this->a0 + this->acy * T_pastCenJ2000;
    float e = this->e0 + this->ecy * T_pastCenJ2000;
    float i = this->I0 + this->Icy * T_pastCenJ2000;
    float L = this->L0 + this->Lcy * T_pastCenJ2000;
    float p = this->long_peri0 + this->long_nodecy * T_pastCenJ2000;
    float W = this->long_node0 + this->long_nodecy * T_pastCenJ2000;

    // Convert angles to radians
    i *= PI/180.f;
    L *= PI/180.f;
    p *= PI/180.f;
    W *= PI/180.f;

    float M = L - p; // mean anomaly
    float w = p - W; // 
    
    // Newton-Raphson in order to get the eccentricity
    float E = M;
    float dE = 0.f;
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

    // P, Q 2d coordinate system
    float P = a * (std::cos(E) - e);
    float Q = a * std::sin(E) * std::sqrt(1 - std::pow(e, 2));

    // rotate by argument of periapsis
    float x = std::cos(w) * P - std::sin(w) * Q;
    float y = std::sin(w) * P + std::cos(w) * Q;
    // rotate by inclination
    float z = std::sin(i) * y;
    y = std::cos(i) * y;
    // rotate by longitude of ascending node
    float xtemp = x;
    x = std::cos(W) * xtemp - std::sin(W) * y;
    y = std::sin(W) * xtemp + std::cos(W) * y;

    // Save in the output
    r[0] = x*UA;
    r[1] = y*UA;
    r[2] = z*UA;
}

void Planet::get_velocity(double T_eph, double* r) const{
    /**
    * @brief Get velocity of planet on the orbit on a given JD date.
    * Epoch: Double representing the JD
    * x : Store variable for x vel
    * y : Store variable for y vel
    * z : Store variable for z vel
    */


}