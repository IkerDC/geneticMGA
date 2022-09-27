#ifndef GENETIC_DEPS_H
#define GENETIC_DEPS_H

#include <vector>
#include "../planet.h"

struct PlanetTimeSet{
    Planet planet;
    float start_window;
    float end_window; 
};

struct ProblemDefinition{
    PlanetTimeSet departure;
    std::vector<PlanetTimeSet> gravityAssits;

    void add_departure(int _p, float min, float max){
        /**
         * @brief Adds departure from _p. Time window [min, max]
         */
    }

    void add_gravity_assit(int _p, float min, float max){
        /**
         * @brief Add a gravity assist at planet _p. Time window [min, max]
         */
    }

};

#endif //GENETIC_DEPS_H