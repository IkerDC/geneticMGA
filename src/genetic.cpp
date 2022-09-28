#include "genetic.h"

ProblemDefinition::ProblemDefinition(){
}

ProblemDefinition::~ProblemDefinition(){
}

void ProblemDefinition::add_departure(int _p, int min, int max){
    
    this->departurePlanet = Planet(_p);
    if(min >= max){
        throw timeRange();
    }
    this->departureWindow = std::make_pair(min, max);
}

void ProblemDefinition::add_flyby(int _p, int min, int max){
    
    this->flybyPlanets.push_back(Planet(_p));
    if(min >= max){
        throw timeRange();
    }
    this->flybyWindows.push_back(std::make_pair(min, max));
}


/*
====================================================================================================================
                                                I N D I V I D U A L                                               ==
====================================================================================================================
*/

Individual::Individual(ProblemDefinition& prob){

}

Individual::~Individual(){

}

void Individual::init(){
    /**
     * @brief Used to initizilize the individual to a random vector of times (within the windows).
     */
    int max_dep = this->problem->departureWindow.second - this->problem->departureWindow.first;
    int dep_time = this->problem->departureWindow.first + rand() % max_dep;
    this->flyTimes.push_back(dep_time);
    
    for(unsigned int i = 0; i < this->flyTimes.size(); i++){
        int fb_time = this->problem->flybyWindows.at(i).first + rand() % (this->problem->flybyWindows.at(i).second - this->problem->flybyWindows.at(i).first);
        this->flyTimes.push_back(fb_time);
    }
}

int Individual::times2bit() const{

}

float Individual::getFlyTime() const{

}

void Individual::evaluate(){

}