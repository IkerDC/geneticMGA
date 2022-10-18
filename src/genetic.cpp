#include "genetic.h"

ProblemDefinition::ProblemDefinition(){
}

ProblemDefinition::~ProblemDefinition(){
}

void ProblemDefinition::add_departure(int _p, float min, float max){
    
    this->planets.push_back(Planet(_p));
    if(min >= max){
        throw timeRange();
    }
    this->departureWindow = {min, max};
}

void ProblemDefinition::add_planet(int _p, float min, float max){
    
    this->planets.push_back(Planet(_p));
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

Individual::Individual(ProblemDefinition* prob){
    this->problem = prob;
    this->cost = 0.f;
    this->fitness = 0.f;
}

Individual::~Individual(){

}


Individual mate(const Individual& partner){
    /**
     * @brief Matting funciton that creates a new individual.
     */
    
}

void Individual::createMutation(){
    /**
     * @brief Generates mutation in the individual.
     */
}


void Individual::init(){
    /**
     * @brief Used to initizilize the individual to a random vector of times (within the windows).
     */
    float max_dep = this->problem->departureWindow.second - this->problem->departureWindow.first;
    float dep_time = this->problem->departureWindow.first + rand() % (int)max_dep;
    this->flyTimes.push_back(dep_time); // first value in vector is departure date in JL format
    
    for(const auto& fb_wind: this->problem->flybyWindows ){
        float fb_time = fb_wind.first + rand() % (int)(fb_wind.second - fb_wind.first);
        this->flyTimes.push_back(fb_time);
    }
}

int Individual::times2bit() const{

}

float Individual::getFlyTime() const{

}

void Individual::evaluate(){
    /**
     * @brief Solves the mga problem. Updates the cost.
     * 
     */

    // Per planets
    for(unsigned int i = 0; i < this->problem->planets.size() - 2; i++){
        double r1[3], v1[3], r2[3], v2[3], r3[3], v3[3];
        double T1 = std::accumulate(this->flyTimes.begin(), this->flyTimes.begin() + i + 1, 0.0); // Times are in format [Departure T, +ΔT1, +ΔT2,..]
        double T2 = std::accumulate(this->flyTimes.begin(), this->flyTimes.begin() + (i + 1) + 1, 0.0);
        double T3 = std::accumulate(this->flyTimes.begin(), this->flyTimes.begin() + (i + 2) + 1, 0.0); 

        orbit::ephemeris(this->problem->planets.at(i).prm, T1, r1, v1); // segfault here
        orbit::ephemeris(this->problem->planets.at(i + 1).prm, T2, r2, v2);
        orbit::ephemeris(this->problem->planets.at(i + 2).prm, T3, r3, v3);

        double v_dep1[3], v_arr2[3], v_dep2[3], v_arr3[3];

        orbit::lambert(r1, r2, (T2 - T1) * DAY2SEC, MU_SUN, v_dep1, v_arr2);
        orbit::lambert(r2, r3, (T3 - T2) * DAY2SEC, MU_SUN, v_dep2, v_arr3);

        double dV, delta, peri;
        orbit::patched_conic(v_arr2, v_dep2, v2, this->problem->planets.at(i + 1).mu, dV, delta, peri);

        // Cost update if departure too.
        std::cout << "------------------------------------------" << std::endl;
        if(i == 0){
            this->updateDepartureCost(norm(v_dep1));
            std::cout << "  Departure cost: " << norm(v_dep1) << "m/s" << std::endl;
        }

        // Cost update
        this->updateCost(this->problem->planets.at(i + 1), dV, delta, peri);


        std::cout << "  Turning angle: " << rad2deg(delta) << "º" << std::endl;
        std::cout << "  Periapsis rad: " << peri << "m" << std::endl;
        std::cout << "  Total dV     : " << dV << "m/s" << std::endl;
    }
}


void Individual::updateCost(const Planet& planet, double dV, double delta, double peri){
    /**
     * @brief Updates the current cost.
     * - Accumulates the delta V of the flyby.
     * - If the flyby is not feasable (too small peri for instance) it increases the cost a lot (to avoid solution evolving).
     */
    // TODO: change to also consider the perigee and maybe the angle too???
    this->cost += dV;

    // Penalty function.
    // this->cost += ; // Penalize low perigee radius.
    // this->cost += ; // Penalize low velocities flybys (can lead to spacecraft planet capture).

}

void Individual::updateDepartureCost(double dV){
    /**
     * @brief Adds departure cost.
     */
    this->cost += dV;
}


/*
====================================================================================================================
                                                P O P U L A T I O N                                               ==
====================================================================================================================
*/
 
Population::Population(const GenOperators params, ProblemDefinition* problem) : geParameters(params), 
                                                                                population(N_POPULATION, Individual(problem)), 
                                                                                newPopulation(N_POPULATION, Individual(problem)){

}

Population::~Population(){

}

void Population::inception(){
    /**
     * @brief Initializes each individual randomly.
     */
    for(auto& ind: this->population){
        ind.init();
    }
}

void Population::sortPopulation(){
    /**
     * @brief Sorts the population vector from fitest to less fit.
     */
    std::sort(this->population.begin(), this->population.end());
}


// ----- Genetic operators. -----
void Population::selection(){
    /**
     * @brief Selects the individuals that will undergo reporduction/crossover.
     */
    if(this->geParameters.roulette){
        // Roulette Operattor - TODO SET AS AND ENUM AND TRY FURTHER METHODS
        
        float sum_adjusted_ft = 0.f;
        float roulette[N_POPULATION];
        
        for(unsigned int i = 0; i < N_POPULATION; i++){
            sum_adjusted_ft += 1/(1 + this->population.at(i).fitness);
        }
        // Roulette wheel
        for(unsigned int j = 0; j < N_POPULATION; j++){
            roulette[j] = (1/(1 + this->population.at(j).fitness)) / (sum_adjusted_ft);
        }

        // Do the selection
        for(unsigned int k = 0; k < N_POPULATION - this->geParameters.elitism; k++){
            float r = rand_d();
            float curr = roulette[0];
            int idx = 0;
            while (r >= curr){
                idx++;
                curr += roulette[idx]; 
            }
            this->newPopulation.push_back(this->population.at(idx));
        }
        
    }
    else{
        // Tournament method
        for(unsigned int i = 1; i < N_POPULATION - this->geParameters.elitism; i++){

            int rnd_idx[this->geParameters.n_tournament];
            for(int r; r < this->geParameters.n_tournament; r++){
                rnd_idx[r] = rand_rng(this->geParameters.elitism, N_POPULATION - this->geParameters.elitism);
            }
            
            float best_fit = -1.f;
            int fitest_idx = -1;
            for(const auto& idx: rnd_idx){
                if(this->population.at(idx).fitness > best_fit){
                    fitest_idx = idx;
                    best_fit = this->population.at(idx).fitness;
                }
            }
            if(fitest_idx == -1){ // sanity check
                throw "Something went wrong during the tournament selection. No fittest than -1.f indivduales where found!";
            }

            this->newPopulation.push_back(this->population.at(fitest_idx)); // selected!
        }
    }

}

void Population::crossOver(){
    /**
     * @brief Cross over two parents
     */

}

void Population::mutate(){
    /**
     * @brief Mutate the generation.
     */
    for(auto ind: this->population){
        if(rand_d() <= this->geParameters.mutation){ // if probability of mutation
            ind.createMutation();
        }
    }
}

void Population::elitism(){
    /**
     * @brief Select the #n most fit individuals and insert them into the next generation.
     */

    // Sanity check
    if(this->newPopulation.size() != 0){
        throw "The new population vector must be cleaned before elitism operator";
    }

    for(unsigned int i = 0; i < this->geParameters.elitism; i++){
        this->newPopulation.push_back(this->population.at(i));
    }
}

// ***** Evolution ******
void Population::evolveNewGeneration(){
    /**
     * @brief Evaluates each individual
     */
    for(auto& ind: this->population){
        ind.evaluate();
        ind.fitness = ind.cost; // delerte me, do somewhere else (TODO);

    }
}

void Population::runGeneration(){
    /**
     * @brief Runs the full genetic algorithm
     */

    int g = 0;
    this->newPopulation.clear();

    while (g < GEN_LIMIT){
        this->evolveNewGeneration();
        this->sortPopulation();
        
        this->elitism();
        this->selection();
        this->crossOver();
        this->mutate();

        this->population = this->newPopulation;
        this->newPopulation.clear();

        g++;
    }

}

