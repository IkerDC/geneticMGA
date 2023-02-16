#include "transfer.h"

Transfer::Transfer(){

}

Transfer::~Transfer(){

}

void Transfer::add_planets(Planet* p1, Planet* p2){
    /**
     * @brief Adds the two reference plantes
     */
    this->p1 = p1;
    this->p2 = p2;
}

void Transfer::compute_transfer(float T){
    /**
     * @brief Computes the transfer between both planets in the class.
     * Sets v_dep and v_arr
     */
    orbit::lambert(this->p1->r_eph, this->p2->r_eph, T, MU_SUN, this->v_dep, this->v_arr);
}
