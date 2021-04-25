//
// Created by lan on 2021/3/30.
//

#include "EAMLS.h"
#include <algorithm>

EAMLS::EAMLS(DataLoader &dataLoader, int p_size) : m_dataLoader(dataLoader), pop_size(p_size){
    this->num_site = dataLoader.site_num;
}

void EAMLS::init_pop(int p_size, int n_site) {
    /**
     * 初始化种群
     * @param p_size: 种群大小
     * @param n_site: 种群中每个个体的长度
     * 更改了全局变量 pop 和 index_m_map
     */
    default_random_engine generator;
    generator.seed(time(nullptr));
    uniform_real_distribution<double> distribution(0.0, 1.0);

    vector<unsigned char> solution;
    unsigned char one_char = 1;
    unsigned char zero_char = 0;
//    int m=0;
    for(int i=0; i<p_size; i++){
        for(int j=0; j<n_site; j++){
            double random_value = distribution(generator);
            if(random_value<=0.5){
                solution.push_back(one_char);
//                m += 1;
            }else{
                solution.push_back(zero_char);
            }
        }
        this->pop.emplace(i, solution);
//        this->index_m_map.emplace(i, m);
//        m = 0;
        solution.clear();
    }
}

bool EAMLS::pair_cmp(const pair<int, double> &x, const pair<int, double> &y) {
    return x.second > y.second;
}

int EAMLS::readjust_single_solution_order(const vector<unsigned char> &solution,
                                          unordered_map<int, vector<pair<int, double> > > &s_order_map) {
    /**
     * Given a solution, obtain candidate locations.
     */
     vector<int> candidate_facility;
     for(int i=0; i<solution.size(); i++){
         if(solution[i] == 1){
             candidate_facility.push_back(i);
         }
     }

     for(int i=0; i<this->num_site; i++){
         // The vector to store facility and its corresponding distance
         vector<pair<int, double> > facility_dist_vector;
         for(int & j : candidate_facility){
             double dist = 0;
             if(i!=j){
                 dist = this->m_dataLoader.site_transCost_map.find(make_pair(i, j))->second;
             }
            facility_dist_vector.emplace_back(j, dist);
         }

         sort(facility_dist_vector.begin(), facility_dist_vector.end(), pair_cmp);

         s_order_map.emplace(i, facility_dist_vector);
     }

     return (int)candidate_facility.size();
}

//void EAMLS::get_all_solution_order_map() {
//    unordered_map<int, vector<pair<int, double> > > s_order_map;
//    for(const auto & s_it: pop){
//        int m_num = this->readjust_single_solution_order(s_it.second, s_order_map);
//        auto it = this->solution_order_map.find(s_it.first);
//
//        if(it != this->solution_order_map.end()){
//            it->second = s_order_map;
//        }else{
//            this->solution_order_map.emplace(s_it.first, s_order_map);
//        }
//
//        auto m_it = this->index_m_map.find(s_it.first);
//        if(m_it != this->index_m_map.end()){
//            m_it->second = m_num;
//        }else{
//            this->index_m_map.emplace(s_it.first, m_num);
//        }
//
//        s_order_map.clear();
//    }
//}

double EAMLS::calculate_fitness(const vector<unsigned char> &solution, double alpha, bool symbol, int solution_index) {
    /**
     * 计算一个个体的fitness value = 1/objective value
     */
    double fitness = 0.0;
    // 每个solution和它对应的facility order vector
    unordered_map<int, vector<pair<int, double> > > s_order_map;
    if(symbol){
        s_order_map = this->solution_order_map.find(solution_index)->second;
    }else{
        this->readjust_single_solution_order(solution, s_order_map);
    }

    auto o_it = s_order_map.find(0);
//    int m_num = (int)o_it->second.size();

    for(auto & i : o_it->second){
        auto site_it = this->m_dataLoader.site_info_map.find(i.first);
        fitness += site_it->second.fixed_cost;
    }

    double part_fitness = 0.0;
    for(int i=0; i<this->num_site; i++){
        auto order_it = s_order_map.find(i);
        auto site_it = this->m_dataLoader.site_info_map.find(i);
        for(int j=0; j<order_it->second.size(); j++){
            part_fitness += site_it->second.demand*order_it->second[j].second*
                    pow(this->m_dataLoader.fail_prob, j)*(1-this->m_dataLoader.fail_prob);
        }

    }
    fitness += alpha*part_fitness;
    return 1/fitness;
}

void EAMLS::mutation(double mutation_rate, unordered_map<int, vector<unsigned char> > &new_pop) {
    default_random_engine generator;
    generator.seed(time(nullptr));
    uniform_real_distribution<double> distribution(0.0, 1.0);
    vector<unsigned char> new_individual;

    for(const auto & p_it: this->pop){
        new_individual = p_it.second;

        for(unsigned char & i: new_individual){
            double random_value = distribution(generator);
            if(random_value <= mutation_rate){
                i = (i+1)%2;
            }
        }
        int num_facility = EAMLS::check_constraint(new_individual);
        if(num_facility < 2){
            this->repair_strategy(new_individual, num_facility);
        }
        new_pop.emplace(p_it.first, new_individual);
        new_individual.clear();
    }
}

void EAMLS::evaluate_pop(unordered_map<int, vector<unsigned char>> &population,
                         unordered_map<int, double> &solution_index_fitness_map, double alpha) {
    for(const auto & p_it: population){
        double fitness = this->calculate_fitness(p_it.second, alpha, false, -1);
        solution_index_fitness_map.emplace(p_it.first, fitness);
    }
}

int EAMLS::check_constraint(vector<unsigned char> &solution) {
    int m_value = 0;

    for(const auto value: solution){
        if(value==1){
            m_value += 1;
        }
        if(m_value >= 2){
            return m_value;
        }
    }

    return m_value;
}

bool EAMLS::fixed_cost_cmp(const pair<int, int> &x, const pair<int, int> &y) {
    return x.second < y.second;
}

void EAMLS::memorable_local_search(unordered_map<int, vector<unsigned char>> &parent_pop,
                                   unordered_map<int, vector<unsigned char>> &mutation_pop, int n,
                                   unordered_set<vector<unsigned char>, vector_hash> &ind_local_search,
                                   unordered_map<int, double> &parent_index_fitness_map,
                                   unordered_map<int, double> &mutation_index_fitness_map,
                                   unordered_set<vector<unsigned char>, vector_hash> &ls_offspring) {
//    unordered_set<vector<unsigned char>, vector_hash >ls_offspring;
    unordered_map<int, vector<unsigned char> > total_parents_pop;
    vector<pair<int, double> > index_fitness_vector;
    int index = 0;
    for(const auto & s_it: parent_pop){
        total_parents_pop.emplace(index, s_it.second);
        const auto & it = parent_index_fitness_map.find(s_it.first);
        index_fitness_vector.emplace_back(index, it->second);
        index += 1;
    }

    for(const auto & s_it: mutation_pop){
        total_parents_pop.emplace(index, s_it.second);
        const auto & it = mutation_index_fitness_map.find(s_it.first);
        index_fitness_vector.emplace_back(index, it->second);
        index += 1;
    }

    sort(index_fitness_vector.begin(), index_fitness_vector.end(), pair_cmp);

    int i=0;
    for(const auto & pair_it: index_fitness_vector){
        const auto s_it = total_parents_pop.find(pair_it.first);
        const auto set_it = ind_local_search.find(s_it->second);

        if(set_it == ind_local_search.end()){
//            unordered_set<vector<unsigned char>, vector_hash> neighbor_inds;
            this->get_all_neighbor(s_it->second, ls_offspring);
            i += 1;
            if(i>n){
                break;
            }
        }
    }
}

void EAMLS::repair_strategy(vector<unsigned char> &solution, int m_value) {
    vector<pair<int, int> > site_fixed_cost;
    for(const auto & s_it: this->m_dataLoader.site_info_map){
        site_fixed_cost.emplace_back(s_it.first, s_it.second.fixed_cost);
    }
    sort(site_fixed_cost.begin(), site_fixed_cost.end(), fixed_cost_cmp);

    if(m_value == 0){
        solution[site_fixed_cost[0].first] = 1;
        solution[site_fixed_cost[1].first] = 1;
    }else if(m_value == 1){
        if(solution[site_fixed_cost[0].first] == 1){
            solution[site_fixed_cost[1].first] = 1;
        }else{
            solution[site_fixed_cost[0].first] = 1;
        }
    }else{
        cout << "Something error! No need to do repair operation!" << endl;
    }
}

void EAMLS::get_all_neighbor(const vector<unsigned char> &solution,
                             unordered_set<vector<unsigned char>, vector_hash> &neighbor_set) {
    for(int i=0; i<solution.size(); i++){
        vector<unsigned char> neighbor_solution = solution;

        neighbor_solution[i] = (neighbor_solution[i]+1)%2;

        int m_value = EAMLS::check_constraint(neighbor_solution);
        if(m_value < 2){
            this->repair_strategy(neighbor_solution, m_value);
        }

        neighbor_set.emplace(neighbor_solution);
    }
}

double EAMLS::get_l3_value(unordered_map<int, vector<unsigned char>> &pop_after_selection,
                           unordered_set<vector<unsigned char>, vector_hash> &all_neighbor_inds) const {
    int num = 0;
    for(const auto & it: pop_after_selection){
        const auto & s_it = all_neighbor_inds.find(it.second);
        if(s_it != all_neighbor_inds.end()){
            num += 1;
        }
    }

    return (double)num/this->pop_size;
}

void EAMLS::survival_selection(unordered_map<int, vector<unsigned char>> &mutation_pop,
                               unordered_set<vector<unsigned char>, vector_hash> &ls_pop,
                               unordered_map<int, double> &mutation_index_fitness_map, double alpha) {
    unordered_map<int, vector<unsigned char> > total_solution;
    vector<pair<int, double> > index_fitness_vector;
    int solution_index = 0;
    for(const auto & s_it: this->pop){
        total_solution.emplace(solution_index, s_it.second);
        const auto f_it = this->index_fitness_map.find(s_it.first);
        index_fitness_vector.emplace_back(make_pair(solution_index, f_it->second));
        solution_index += 1;
    }
    for(const auto & s_it: mutation_pop){
        total_solution.emplace(solution_index, s_it.second);
        const auto f_it = mutation_index_fitness_map.find(s_it.first);
        index_fitness_vector.emplace_back(make_pair(solution_index, f_it->second));
        solution_index += 1;
    }

    for(const auto & s_it: ls_pop){
        total_solution.emplace(solution_index, s_it);
        double fitness = this->calculate_fitness(s_it, alpha, false, -1);
        index_fitness_vector.emplace_back(make_pair(solution_index, fitness));
        solution_index += 1;
    }

    sort(index_fitness_vector.begin(), index_fitness_vector.end(), pair_cmp);

    this->pop.clear();
    this->index_fitness_map.clear();
//    cout << "pop_size = " << this->pop_size << endl;
//    cout << "total_solution_size = " << total_solution.size() << endl;
    if(this->pop_size > total_solution.size()){
        this->pop_size = (int)total_solution.size();
    }
    for(int i=0; i<this->pop_size; i++){
        const auto s_it = total_solution.find(index_fitness_vector[i].first);
        this->pop.emplace(i, s_it->second);
        this->index_fitness_map.emplace(i, index_fitness_vector[i].second);
    }
}

double EAMLS::EA_with_MLS(int generation_num, double mutation_rate, double beta, int step_size, int n) {
    this->init_pop(this->pop_size, this->num_site);
    unordered_set<vector<unsigned char>, vector_hash> all_neighbor_inds;
//    unordered_map<int, double> index_fitness
    this->evaluate_pop(this->pop, this->index_fitness_map, this->alpha_value);

    unordered_map<int, vector<unsigned char> > pop_after_mutation;
    unordered_map<int, double> mutation_index_fitness_map;
    unordered_set<vector<unsigned char>, vector_hash> ls_offspring;
    for(int i=0; i<generation_num; i++){
//        cout << "current generation_num = " << i << endl;
        this->mutation(mutation_rate, pop_after_mutation);
        this->evaluate_pop(pop_after_mutation, mutation_index_fitness_map, this->alpha_value);

        this->memorable_local_search(this->pop, pop_after_mutation, n, all_neighbor_inds,
                                      this->index_fitness_map, mutation_index_fitness_map, ls_offspring);

        this->survival_selection(pop_after_mutation, ls_offspring, mutation_index_fitness_map,
                                 this->alpha_value);
        double l3_value = this->get_l3_value(this->pop, all_neighbor_inds);
        if(l3_value > beta){
            this->pop_size += step_size;
        }

        for(const auto& solution: ls_offspring){
            all_neighbor_inds.emplace(solution);
        }

        pop_after_mutation.clear();
        mutation_index_fitness_map.clear();
        ls_offspring.clear();
    }

//    vector<pair<int, double> > s_f_vector;
    double fitness_value = 0.0;
    for(const auto & it: this->index_fitness_map){
        if(it.second > fitness_value){
            fitness_value = it.second;
        }
    }
//    sort(s_f_vector.begin(), s_f_vector.end(), pair_cmp);

//    cout << s_f_vector[0].first << "=" << 1/s_f_vector[0].second << endl;
//
//    const auto & best_solution = this->pop.find(s_f_vector[0].first);
//
//    for(unsigned char ki: best_solution->second){
//        cout << (int)ki << ", ";
//    }
//    cout << endl;
//    cout << "***********************************" << endl;

    return 1/fitness_value;

}

