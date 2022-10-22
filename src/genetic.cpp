#include "genetic.h"

ProblemDefinition::ProblemDefinition(const int _dep) : departure(_dep){
}

ProblemDefinition::~ProblemDefinition(){
}

void ProblemDefinition::add_planet(int _p, int min, int max){
    
    this->planets.push_back(Planet(_p));
    if(min >= max){
        throw timeRange();
    }

    this->timeWindows.push_back(std::make_pair(min, max));
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


Individual Individual::mate(const Individual& partner, int crossType){
    /**
     * @brief Matting function that creates a new individual.
     */
    if(crossType == CROSS_UNIFORM){
        // Take the full chromosomes. Pick randmly the bit for the child from one of the parents.
        for(unsigned int i = 0; i < this->flyTimes.size(); i++){
            std::string p1_g = int2bitStr(this->flyTimes.at(i));
            std::string p2_g = int2bitStr(partner.flyTimes.at(i));
            std::string child_g = uniformBitstrCross(p1_g, p2_g);

            int child_time = bitStr2int(child_g);
            // Check that the new gene is within the problem's bounds. Else, adjust them. NOTE: not ideal (maybe could be added to the penalty function).
            child_time = (child_time >= this->problem->timeWindows.at(i).first) ? child_time : this->problem->timeWindows.at(i).first;
            child_time = (child_time <= this->problem->timeWindows.at(i).second) ? child_time : this->problem->timeWindows.at(i).second;
            // FIXME: Individual child = this; child.flyTimes.at(i) = child_time;   
            

        }
    }
    else if(crossType == CROSS_SINGLE_GENE){
        // Select a random Gene. Do CROSS_UNIFORM only on that gene.
        const int r_gene = rand() % this->flyTimes.size();
        std::string p1_g = int2bitStr(this->flyTimes.at(r_gene));
        std::string p2_g = int2bitStr(partner.flyTimes.at(r_gene));
        std::string child_g = uniformBitstrCross(p1_g, p2_g);

        int child_time = bitStr2int(child_g);
        // Check that the new gene is within the problem's bounds. Else, adjust them. NOTE: not ideal (maybe could be added to the penalty function).
        child_time = (child_time >= this->problem->timeWindows.at(r_gene).first) ? child_time : this->problem->timeWindows.at(r_gene).first;
        child_time = (child_time <= this->problem->timeWindows.at(r_gene).second) ? child_time : this->problem->timeWindows.at(r_gene).second;
        // FIXME: Individual child = this; child.flyTimes.at(r_gene) = child_time;   

    }
    else if(crossType == CROSS_SINGLE_POINT){
        // From the full chromosome. At a given random point, interchange the parent 1 bits by the partner's bits.
        std::string p1_chromo;
        std::string p2_chromo;
        for(unsigned int i = 0; i < this->flyTimes.size(); i++){
            p1_chromo.append(int2bitStr(this->flyTimes.at(i)));
            p2_chromo.append(int2bitStr(partner.flyTimes.at(i)));
        }
        
        const int cut_at = std::rand() % p1_chromo.size();
        std::string child;
        child.append(p1_chromo.substr(0, cut_at)); // Start to cut_at.
        child.append(p2_chromo.substr(cut_at)); // from cut_at pos to end.

        // Convert now to actual times 
        for(unsigned int j = 0; j < this->flyTimes.size(); j++){
            //FIXME: The individual has to be created
            //ind.flyTimes.at(i) = bitStr2int(child.substr(j * MAX_BIT_SIZE, MAX_BIT_SIZE)); // From pos, and take the next MAX_BIT_SIZE
        }
    }
    else if(crossType == CROSS_DOUBLE_POINT){
        // From the full chromosome. At a given random point 1, interchange the parent 1 bits by the partner's bits. Do the same a second time at point 2.
        std::string p1_chromo;
        std::string p2_chromo;
        for(unsigned int i = 0; i < this->flyTimes.size(); i++){
            p1_chromo.append(int2bitStr(this->flyTimes.at(i)));
            p2_chromo.append(int2bitStr(partner.flyTimes.at(i)));
        }
        
        const int cut_at_1 = rand_rng(1, p1_chromo.size() - 2); // From above 1, to at least leave 1 for the second cut.
        const int cut_at_2 = rand_rng(cut_at_1 + 1,  p1_chromo.size() - 1); // From at least one bit after cut one to end leave at least one for this cut.
        std::string child;
        child.append(p1_chromo.substr(0, cut_at_1)); 
        child.append(p2_chromo.substr(cut_at_1, cut_at_2 - cut_at_1));
        child.append(p1_chromo.substr(cut_at_2));

        // Convert now to actual times 
        for(unsigned int j = 0; j < this->flyTimes.size(); j++){
            //FIXME: The individual has to be created
            //ind.flyTimes.at(i) = bitStr2int(child.substr(j * MAX_BIT_SIZE, MAX_BIT_SIZE)); // From pos, and take the next MAX_BIT_SIZE
        }
    }
    else{
        throw "Unkown crossover type!";
    }
    
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
    for(const auto& window: this->problem->timeWindows){
        int t = window.first + rand() % (window.second - window.first);
        this->flyTimes.push_back(t);
    }
}


int Individual::getFlyTime() const{

}

void Individual::evaluate(){
    /**
     * @brief Solves the mga problem. Updates the cost.
     * 
     */

    // Per planets
    for(unsigned int i = 0; i < this->problem->planets.size() - 2; i++){
        double r1[3], v1[3], r2[3], v2[3], r3[3], v3[3];
        double T1 = this->problem->departure + std::accumulate(this->flyTimes.begin(), this->flyTimes.begin() + i + 1, 0.0); // Times are in format [Departure T, +ΔT1, +ΔT2,..]
        double T2 = this->problem->departure + std::accumulate(this->flyTimes.begin(), this->flyTimes.begin() + (i + 1) + 1, 0.0);
        double T3 = this->problem->departure + std::accumulate(this->flyTimes.begin(), this->flyTimes.begin() + (i + 2) + 1, 0.0); 

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
        std::cout << "  Fitness      : " << this->cost << std::endl;  
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
    if(this->geParameters.selectionType == SELECTION_ROULETTE){
        // Roulette Operattor - TODO SET AS AND ENUM AND TRY FURTHER METHODS
        
        float sum_adjusted_ft = 0.f;
        float roulette[N_POPULATION];
        
        for(unsigned int i = 0; i < N_POPULATION; i++){
            sum_adjusted_ft += 1/(1 + this->population.at(i).fitness);
        }
        // Roulette wheel
        std::cout << std::endl << "Fitness: ";
        for(unsigned int j = 0; j < N_POPULATION; j++){
            roulette[j] = (1/(1 + this->population.at(j).fitness)) / (sum_adjusted_ft);
            std::cout << roulette[j] << ", ";
        }
        std::cout << std::endl;

        // Do the selection
        for(unsigned int k = 0; k < N_POPULATION - this->geParameters.elitism_n; k++){
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
    else if(this->geParameters.selectionType == SELECTION_TOURNAMENT){
        // Tournament method
        for(unsigned int i = 1; i < N_POPULATION - this->geParameters.elitism_n; i++){

            int rnd_idx[TOURNAMENT_N];
            for(int r; r < TOURNAMENT_N; r++){
                rnd_idx[r] = rand_rng(this->geParameters.elitism_n, N_POPULATION - this->geParameters.elitism_n);
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
    else{
        throw "Unknow selection method";
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
        if(rand_d() <= this->geParameters.mutationProb){ // if probability of mutation
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

    for(unsigned int i = 0; i < this->geParameters.elitism_n; i++){
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
        ind.fitness = ind.cost; // delerte me, do somewhere else (TODO:);
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

