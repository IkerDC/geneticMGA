#include "flyby.h"
#include "utilities.h"
#include "pagmo/Astro_Functions.h"
#include "math.h"


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

void FlyBy::get_deltaV(double* dv){
    dv[0] = this->dv[0];
    dv[1] = this->dv[1];
    dv[2] = this->dv[2];
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
     */

    double v_in_rel[3]; //Vincom
    double v_out_rel[3]; //Vou
    
    // Relative velocities to the planet
    //v_in_rel = norm(v_in, this->v_planet);
    //v_out_rel = norm(v_out, this->v_planet);

    for(unsigned int i = 0; i < 3; i++){
        v_in_rel[i] = v_in[i] - this->v_planet[i];
        v_out_rel[i] = v_out[i] - this->v_planet[i];
    }

    float dV = fb_vel(v_in_rel, v_out_rel, 643428000.0,this->planet->mu);

    float a = 0;
    // semi-major axis of trajectories
    double a_in = -this->planet->mu/(norm2(v_in_rel)*norm2(v_in_rel));
    double a_out = -this->planet->mu/(norm2(v_out_rel)*norm2(v_out_rel));

    //N-R to solve the eccentricity outwards
    float e_out = 1.5f; //Initial value (from paper)
    float de_out = 0.f;
    float alpha = 0.f;
    unsigned int iter = 0;
    while (true){
        alpha = std::asin(1/((a_out/a_in)*(e_out-1)+1))+std::asin(1/e_out);
        de_out = ((a_out/a_in)*e_out-(a_out/a_in)+1) * ((std::cos(alpha-std::asin(1/e_out)))/(e_out*e_out*std::sqrt(1-1/(e_out*e_out)))) + ((a_out/a_in) * std::sin(alpha - std::asin(1/e_out)));
        e_out -= de_out;
        if(std::abs(de_out) < 1e-6){
            break;
        }
        if(iter > 10000){
            std::cout << "Iteration limit hit on N-R fyby outgoing eccenticity computation." << std::endl;
            break;
        }
        iter++;
    }

    float radi_peri = a_out * (1-e_out);
    float dv = std::abs(std::sqrt(norm2(v_in)+(2*this->planet->mu/radi_peri))-std::sqrt(norm2(v_out)+(2*this->planet->mu/radi_peri)));
    std::cout << "The radi is: " << radi_peri << std::endl;
    std::cout << "The abs dv required is of: " << dv << std::endl;
}

