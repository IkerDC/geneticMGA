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

/*
====================================================================================================================
                                                P O P U L A T I O N                                               ==
====================================================================================================================
*/
 
Population::Population(const GenOperators params, ProblemDefinition& problem) : geParameters(params), 
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
        float roulette[N_POPULATION - this->geParameters.elitism];
        
        for(unsigned int i = 0; i < N_POPULATION - this->geParameters.elitism; i++){
            sum_adjusted_ft += 1/(1 + this->population.at(i + this->geParameters.elitism).fitness);
        }
        // Roulette wheel
        for(unsigned int j = 0; j < N_POPULATION - this->geParameters.elitism; j++){
            roulette[j] = (1/(1 + this->population.at(j + this->geParameters.elitism).fitness)) / (sum_adjusted_ft);
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
            this->newPopulation.push_back(this->population.at(idx + this->geParameters.elitism));
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
    }
}

void Population::runGeneration(){

}

