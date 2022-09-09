
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
    p.compute_eph();
    this->planets.push_back(p);

}

void MGAProblem::add_planet(const int planet, std::string at){
    /**
     * @brief Adds a new planet given the name and a time in str format as YYYY-MM-DD
     */
    float at_jd = date2jd(at);
    
    Planet p = Planet(planet, at_jd);
    p.compute_eph();
    this->planets.push_back(p);
}

void MGAProblem::compute_transfers(){
    /**
     * @brief Will compute the different transfers between all the planets.
     * Per pair of planets in the problem it will solve the Lambert problem and save it in the class's attribute.
     */

    for(unsigned int i = 0; i < this->planets.size() - 1; i++){
        //std::cout << "Planet 1:" << &this->planets.at(i) << " Planet 2:" << &this->planets.at(i+1) << std::endl; 
        Transfer t = Transfer();
        t.add_planets(&this->planets.at(i), &this->planets.at(i+1));
        //std::cout << "After  1:" << t.p1 << " AFter  2: "<< t.p2 << std::endl;
        t.compute_transfer();
        this->transfers.push_back(t);
        //std::cout << "After  1:" << this->transfers.at(i).p1 << " AFter  2: "<< this->transfers.at(i).p2 << std::endl;
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