#include "orbital_mechanics.h"


void orbit::ephemeris(const Planet& planet, const double T, double* r, double* v){ //Outputs
    /**
     * @brief Computes the ephemeris of a given planet. 
     * Returns position and speed.
     */

    double T_pastCenJ2000 = (T - 2451545.0)/36525;

    // Orbital elements
    double a = planet.a0 + planet.acy * T_pastCenJ2000;
    double e = planet.e0 + planet.ecy * T_pastCenJ2000;
    double i = planet.I0 + planet.Icy * T_pastCenJ2000;
    double L = planet.L0 + planet.Lcy * T_pastCenJ2000;
    double p = planet.long_peri0 + planet.long_nodecy * T_pastCenJ2000;
    double W = planet.long_node0 + planet.long_nodecy * T_pastCenJ2000;

    // Convert angles to radians
    i *= PI/180.0;
    L *= PI/180.0;
    p *= PI/180.0;
    W *= PI/180.0;

    double M = L - p;
    double w = p - W; 
    
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
    double vP = - (a * std::sin(E) * planet.Lcy) / (1 - e * std::cos(E));
    double vQ = (a * std::cos(E) * std::sqrt(1 - e*e) * planet.Lcy) / (1 - e * std::cos(E));

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


void orbit::lambert(){
    /**
     * @brief Lambert solver. Given the ephemeris of two planets, and time of flight T.
     * It computes the heliocentric transfer speeds. Essentialy transfer orbit in heliocentric reference frame.
     */

}

void orbit::patched_conic(const double* Vin, const double* Vout, const double* Vplanet, const Planet& planet, //Input
                            double& dV, double& delta, double& peri){ //Output
    /**
     * @brief Used to pacth the two Lamebrt solutions. 
     * Takes the incoming and outgoing heliocentric velocities, converts it to planetocentric velocities (relative hyperbolic)
     * Then solves the required dV, turning angle and perigee radius to join the two trajectories.
     */

    //Convert to planetocentric velocities. relative hyperbolic. 
    std::cout << "Flyby at: -----------------------------" << std::endl;
    double VinRel[3];
    double VoutRel[3];

    minus2(Vin, Vplanet, VinRel);
    minus2(Vout, Vplanet, VoutRel);

    double ain = -planet.mu/vec2(VinRel);
    double aout = -planet.mu/vec2(VoutRel);
    double e;


    delta = std::acos(dot_prod(VinRel, VoutRel)/(norm(VinRel) * norm(VoutRel)));
    e = 1/std::sin((delta/2));
    peri = aout*(1-e); 
    dV = std::fabs(std::sqrt(vec2(VinRel) + ((2*planet.mu)/(peri))) - std::sqrt(vec2(VoutRel) + ((2*planet.mu)/(peri))));

    std::cout << "Relative velocity Vin: " << norm(VinRel) << " [m/s]"<< std::endl;
    std::cout << "Relative velocity Vout: " << norm(VoutRel) << " [m/s]"<< std::endl;
    std::cout << "Turning angle: " << delta << " [rad]"<< std::endl;
    std::cout << "Eccentricity " << e << std::endl;
    std::cout << "Periapsis radius " << peri << " [m]"<< std::endl;
    std::cout << "Total dV " << dV << " [m/s]"<< std::endl;
    
}
