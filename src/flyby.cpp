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

    if (t1->p2 != t2->p1){
        std::cout << "Error. Flyby planet are is not the same. Transfer 1 arrival planet must be the same as transfer 2 departure planet" << std::endl;
        throw distinctFlybyPlanet();
    }

    this->planet = this->trans1->p2;
}

void Flyby::compute_flyby(){
    /**
     * @brief Computes the flyby. 
     */
    orbit::patched_conic(this->trans1->v_arr, this->trans2->v_dep, this->planet->v_eph, this->planet->mu, this->dV, this->delta, this->peri);
}
