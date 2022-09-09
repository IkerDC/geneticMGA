#include "transfer.h"

Transfer::Transfer(){

}

Transfer::~Transfer(){

}

void Transfer::add_planets(Planet* p1, Planet* p2){
    /**
     * @brief Adds the two reference plantes
     */
    //std::cout << "Added  1:" << p1 << " Added  2: "<< p2 << std::endl;
    this->p1 = p1;
    this->p2 = p2;
    this->T = this->p2->at - this->p1->at;

    if (this->T <= 0){
        std::cout << "Error. Transfer times between planets is negative. Planet 2 arrival time is before planet 1 departure time." << std::endl;
        throw negativeTime();
    }
}

void Transfer::compute_transfer(){
    /**
     * @brief Computes the transfer between both planets in the class.
     */
    orbit::lambert(this->p1->r_eph, this->p2->r_eph, this->T, MU_SUN, this->v_dep, this->v_dep);
}

void Transfer::print() const{

}