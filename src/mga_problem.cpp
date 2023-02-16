#include <stdlib.h>
#include "mga_problem.h"

MGAProblem::MGAProblem(){
    
}

MGAProblem::MGAProblem(const Individual ind){
    /**
     * @brief Constructor out of an individual, to better anaylze it.
     * It has to convert the raw solution of dates to real dates, as: Dep + t0 + t1 + t2
     * Dates are incresing (see the thesis).
     */
    float increase = ind.problem->departure; // Init at start of departure window.
    
    for(unsigned int i = 0; i < ind.problem->planets.size(); i++){
        this->planets.push_back(ind.problem->planets.at(i));            // Add planet to vector.
        this->times.push_back((float)(ind.flyTimes.at(i) + increase));  // Add the date at that planet.
        increase += (float)ind.flyTimes.at(i);                          // Increase the time. 
    }
}

MGAProblem::~MGAProblem(){

}

void MGAProblem::add_planet(const int planet, float at){
    /**
     * @brief Adds a new planet given the name and a time in JD.
     * Usually called when the class is build with the default constructor (not using and individual).
     * If needed to compute a trajectory "by hand", planet and date are provided.
     */
    Planet p = Planet(planet);  // Create planet
    this->planets.push_back(p); // Add planet
    this->times.push_back(at);  // Add time
}

void MGAProblem::compute_ephemeris(){
    /**
     * @brief Computes the ephermeris of the planets in the class.
     */
    for(unsigned int i = 0; i < this->planets.size(); i++){
        this->planets.at(i).compute_eph(this->times.at(i));
    }
}

void MGAProblem::compute_transfers(){
    /**
     * @brief Will compute the different transfers between all the planets.
     * Per pair of planets in the problem it will solve the Lambert problem and save it in the class's attribute.
     */

    for(unsigned int i = 0; i < this->planets.size() - 1; i++){
        Transfer t = Transfer();
        t.add_planets(&this->planets.at(i), &this->planets.at(i+1));    // Sets the planets references on the new transfer instance.
        float T = (this->times.at(i+1) - this->times.at(i)) * DAY2SEC;  // Duration of travel in seconds.
        t.compute_transfer(T);                                          // Compute transfer
        this->transfers.push_back(t);                                   // Add the transfer instance to the class
    }

}
void MGAProblem::compute_flybys(){
    /**
     * @brief Will compute the flyby at each correspondant planet.
     * Per pair of transfers ending and beging at a certian planet, it will use patched conic to solve the two transfers.
     */
    for(unsigned int i = 0; i < this->transfers.size() - 1; i++){
        Flyby f = Flyby();
        f.add_planet_transfer(&this->transfers.at(i), &this->transfers.at(i+1));    // Sets planet of flyby reference
        f.compute_flyby();                                                          // Compute flyby
        this->flybys.push_back(f);                                                  // Add flyby instance to class.
    }

}

void MGAProblem::compute(){
    this->compute_ephemeris();
    this->compute_transfers();
    this->compute_flybys();
}

void MGAProblem::plot() const{
    /**
     * @brief Plots the solution to the problem
     * Loads the solution to a json file. Call to an pyhton script that interprets it and plots the problem solution.
     * To plot the problem, the trajectory is described in a json file called "visualize.json".
     * ALl the necesary data to plot is wrote there. Other options as colors can be set.
     */

    // Init the json object that will go to the file.
    nlohmann::json visual_js = {
        {"Planets", {}},
        {"Transfers", {}},
        {"Extra",{}}
    };

    // Fill the planets and the coordinates
    for(unsigned int i = 0; i < this->planets.size(); i++){
        visual_js["Planets"].push_back({
            {"Name", planets.at(i).name},
            {"At", times.at(i)},
            {"Coordinates", planets.at(i).r_eph},
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

    // Fill the extra (extra info that was used in some moment.)
    visual_js["Extra"] = {{"Departure", this->times.at(0)},{"Arrival", this->times.back()}};
    

    // Write file
    std::ofstream outfile("visuals/visualize.json");
    outfile << std::setw(4) << visual_js << std::endl;

    // call excutable script that plots.
    int status = system("python3 visuals/main.py &");

    if (status != EXIT_SUCCESS){
        std::cout << "Error code while executing the python visualizer. Code: " << status << std::endl;
    }

}

void MGAProblem::print() const{
    /**
     * @brief Pretty print of the whole problem.
     */
    double dep[3];
    minus2(this->transfers.at(0).v_dep, this->planets.at(0).v_eph, dep);
    
    std::cout << "** Departure cost: "<< norm(dep) << "m/s" << std::endl;
    for(const auto& fb: this->flybys){
        std::cout << "=== FLYBY at: " << fb.planet->name << " ===" << std::endl;
        fb.print();
    }
    std::cout << "** Arrival speed: "<< norm(this->transfers.back().v_arr) << "m/s" << std::endl;
    std::cout << std::endl;
}