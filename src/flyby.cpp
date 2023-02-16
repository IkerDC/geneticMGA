#include "flyby.h"

Flyby::Flyby(){

}

Flyby::~Flyby(){

}

void Flyby::add_planet_transfer(Transfer* t1, Transfer* t2){
    /**
     * @brief Fills the transfers and planet for the flyby.
     */
    this->trans1 = t1;
    this->trans2 = t2;

    // Sanity check, they are not the same planet.
    if (t1->p2 != t2->p1){
        std::cout << "Error. Flyby planet are is not the same. Transfer 1 arrival planet must be the same as transfer 2 departure planet" << std::endl;
        throw distinctFlybyPlanet();
    }

    // Flyby planet is the arriving planet in transfer 1 or departing planet in transfer 2... We read it from there.
    this->planet = this->trans1->p2;
}

void Flyby::compute_flyby(){
    /**
     * @brief Computes the flyby. 
     */
    orbit::patched_conic(this->trans1->v_arr, this->trans2->v_dep, this->planet->v_eph, this->planet->mu, this->dV, this->delta, this->peri);
    
    // Sets the relative velocities of the spacecraft.
    // v_rel = v_spacraft - v_planet
    // Does not return anything because it is set directly using references.
    minus2(this->trans1->v_arr, this->planet->v_eph, this->v_in_rel); 
    minus2(this->trans2->v_dep, this->planet->v_eph, this->v_out_rel);
}

void Flyby::print() const{
    /**
     * @brief Pretty-rint the solution.
     */
    std::cout << "  Incoming velocity (relative): " << norm(this->v_in_rel) << " m/s" << std::endl;
    std::cout << "  Outgoing velocity (relative): " << norm(this->v_out_rel) << " m/s" << std::endl;
    std::cout << "  Turning angle: " << rad2deg(this->delta) << "º"<< std::endl;
    std::cout << "  Periapsis rad: " << this->peri << " m"<< std::endl;
    std::cout << "  Total dV     : " << this->dV << " m/s"<< std::endl;
}