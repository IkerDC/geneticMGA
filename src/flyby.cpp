#include "flyby.h"
#include "utilities.h"
#include "pagmo/Astro_Functions.h"


FlyBy::FlyBy(Planet* p, float T) : planet(p), T(T){


}
FlyBy::~FlyBy(){

}

void FlyBy::set_planet_v(double* v){
    this->v_planet[0] = v[0];
    this->v_planet[1] = v[1];
    this->v_planet[2] = v[2];
}

void FlyBy::set_incoming_v(double* v){
    this->v_in[0] = v[0];
    this->v_in[1] = v[1];
    this->v_in[2] = v[2];
}

void FlyBy::set_outgoing_v(double* v){
    this->v_out[0] = v[0];
    this->v_out[1] = v[1];
    this->v_out[2] = v[2];
}

double* FlyBy::get_deltaV(){
    return this->dv;
}

double FlyBy::get_total_deltaV() const{
    return norm2(this->dv);
}

float FlyBy::get_periphasis() const{
    return this->peri;
}

void FlyBy::compute_flyby(){
    /**
     * @brief Standart pacthech conic approximation to get required DeltaV at flyby periphasis.
     * Following AIAA 2012-4592, Section 2.A
     */

    double v_in_rel[3];
    double v_out_rel[3];
    // Relative velocities to the planet
    for(unsigned int i = 0; i < 3; i++){
        v_in_rel[i] = this->v_in[i] - this->v_planet[i];
        v_out_rel[i] = this->v_out[i] - this->v_planet[i];
    }

    if(this->planet == nullptr){
        throw PlanetUnreferended();
    }

    // semi-major axis of trajectories
    


}

