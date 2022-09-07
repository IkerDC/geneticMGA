
#include "mga_problem.h"

MGAProblem::MGAProblem(){

}
MGAProblem::~MGAProblem(){

}

void MGAProblem::add_planet(const int planet, float at){
    /**
     * @brief Adds a new planet given the name and a time in JD
     */
    this->planets.push_back(Planet(planet, at));
}

void MGAProblem::add_planet(std::string planet, std::string at){
    /**
     * @brief Adds a new planet given the name and a time in str format as YYYY-MM-DD
     */
    

}
void MGAProblem::compute_transfers(){

}
void MGAProblem::compute_flybys(){

}

double MGAProblem::computeCost() const{

}
bool MGAProblem::isSolutionValid() const{

}

void MGAProblem::plot() const{

}
void MGAProblem::print() const{
    
}