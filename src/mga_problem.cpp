
#include "mga_problem.h"

MGAProblem::MGAProblem(){

}
MGAProblem::~MGAProblem(){

}

void MGAProblem::add_planet(const int planet, float at){
    /**
     * @brief Adds a new planet given the name and a time in JD
     */
    Planet p = Planet(planet, at);
    this->planets.push_back(p);

}

void MGAProblem::add_planet(const int planet, std::string at){
    /**
     * @brief Adds a new planet given the name and a time in str format as YYYY-MM-DD
     */
    float at_jd = date2jd(at);
    Planet p = Planet(planet, at_jd);
    this->planets.push_back(p);
}

void MGAProblem::compute_ephemeris(){
    /**
     * @brief Computes the ephermeris of the planets in the class.
     */
    for(unsigned int i = 0; i < this->planets.size(); i++){
        this->planets.at(i).compute_eph();
    }
}

void MGAProblem::compute_transfers(){
    /**
     * @brief Will compute the different transfers between all the planets.
     * Per pair of planets in the problem it will solve the Lambert problem and save it in the class's attribute.
     */

    for(unsigned int i = 0; i < this->planets.size() - 1; i++){
        Transfer t = Transfer();
        t.add_planets(&this->planets.at(i), &this->planets.at(i+1));
        t.compute_transfer();
        this->transfers.push_back(t);
    }

}
void MGAProblem::compute_flybys(){
    /**
     * @brief Will compute the flyby at each correspondant planet.
     * Per pair of transfers ending and beging at a certian planet, it will use patched conic to solve the two transfers.
     */
    for(unsigned int i = 0; i < this->transfers.size() - 1; i++){
        Flyby f = Flyby();
        f.add_planet_transfer(&this->transfers.at(i), &this->transfers.at(i+1));
        f.compute_flyby();
        this->flybys.push_back(f);
    }

}

double MGAProblem::computeCost() const{

}

bool MGAProblem::isSolutionValid() const{

}

void MGAProblem::plot() const{

}

void MGAProblem::print() const{
    
}