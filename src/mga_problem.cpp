#include <stdlib.h>
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
    /**
     * @brief Plots the solution to the problem
     * Loads the solution to a json file. Call to an pyhton script that interprets it and plots the problem solution.
     */

    // Fills the json file.
    nlohmann::json visual_js = {
        {"Planets", {}},
        {"Transfers", {}}
    };

    // Fill the planets and the coordinates
    for(const auto& planet: this->planets){
        visual_js["Planets"].push_back({
            {"Name", planet.name},
            {"At", planet.at},
            {"Coordinates", planet.r_eph},
            {"Color", "gray"}
        });
    }

    // Fill the transfers
    for(const auto& transfer: this->transfers){
        visual_js["Transfers"].push_back({
            {"Velocity", transfer.v_dep},
            {"Color", "teal"}
        });
    }

    // Write file
    std::ofstream outfile("visuals/visualize.json");
    outfile << std::setw(4) << visual_js << std::endl;

    // call excutable
    int status = system("python3 visuals/main.py &");

    if (status != EXIT_SUCCESS){
        std::cout << "Error code while executing the python visualizer. Code: " << status << std::endl;
    }

}

void MGAProblem::print() const{
    /**
     * @brief Pretty print of the whole problem.
     */
    for(const auto& fb: this->flybys){
        std::cout << "=== FLYBY at: " << fb.planet->name << " ===" << std::endl;
        fb.print();
    }
}