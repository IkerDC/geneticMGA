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

void Planet::get_position(double T_eph, float &xx, float &yy, float &zz) const{
    /**
    * @brief Get position of planet on the orbit on a given JD date.
    * Epoch: Double representing the JD
    * x : Store variable for x pos
    * y : Store variable for y pos
    * z : Store variable for z pos
    */

    float T_pastCenJ2000 = (T_eph - 2451545.0)/36525;

    float a = this->a0 + this->acy * T_pastCenJ2000;
    float M = this->L0 - this->long_peri0; // mean anomaly
    float w = this->long_peri0 - this->long_node0; 

    // Newton-Raphson in order to get the eccentricity
    float E = M;
    float dE = 0.f;
    while (true){
        dE = (E - this->e0 * std::sin(E) - M)/(1 - this->e0 * std::cos(E));
        E -= dE;
        if(std::abs(dE) < 1e-6){
            break;
        }
    }
    // P, Q 2d coordinate system
    float P = a * (std::cos(E) - this->e0);
    float Q = a * std::sin(E) * std::sqrt(1 - std::pow(this->e0, 2));

    // rotate by argument of periapsis
    float x = std::cos(w) * P - std::sin(w) * Q;
    float y = std::sin(w) * P + std::cos(w) * Q;
    // rotate by inclination
    float z = std::sin(this->I0) * y;
    y = std::cos(this->I0) * y;
    // rotate by longitude of ascending node
    float xtemp = x;
    x = std::cos(w) * xtemp - std::sin(w) * y;
    y = std::sin(w) * xtemp + std::cos(w) * y;


    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;

    xx = x;
    yy = y;
    zz = z;
}

void Planet::get_velocity(double T_eph, float &x, float &y, float &z) const{

}