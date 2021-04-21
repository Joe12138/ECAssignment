//
// Created by lan on 2021/3/30.
//

#include "EAMLS.h"
#include <algorithm>

EAMLS::EAMLS(DataLoader &dataLoader, int p_size) : m_dataLoader(dataLoader), pop_size(p_size){
    this->num_site = dataLoader.site_num;
}

void EAMLS::init_pop(int p_size, int n_site) {
    default_random_engine generator;
    generator.seed(time(nullptr));
    uniform_real_distribution<double> distribution(0.0, 1.0);

    vector<unsigned char> solution;
    unsigned char one_char = 1;
    unsigned char zero_char = 0;
    int m=0;
    for(int i=0; i<p_size; i++){
        for(int j=0; j<n_site; j++){
            double random_value = distribution(generator);
            if(random_value<=0.5){
                solution.push_back(one_char);
                m += 1;
            }else{
                solution.push_back(zero_char);
            }
        }
        this->pop.emplace(i, solution);
        this->index_m_map.emplace(i, m);
        m = 0;
        solution.clear();
    }
}

bool EAMLS::pair_cmp(const pair<int, double> &x, const pair<int, double> &y) {
    return x.second < y.second;
}

void EAMLS::readjust_single_solution_order(int solution_index) {
    /**
     * Given a solution, obtain candidate locations.
     */
     auto s_it = this->pop.find(solution_index);
     vector<int> candidate_facility;
     for(int i=0; i<s_it->second.size(); i++){
         if(s_it->second[i] == 1){
             candidate_facility.push_back(i);
         }
     }

     unordered_map<int, vector<pair<int, double> > > s_order_map;
     for(int i=0; i<this->num_site; i++){
         // The vector to store facility and its corresponding distance
         vector<pair<int, double> > facility_dist_vector;
         for(int & j : candidate_facility){
             double dist = this->m_dataLoader.site_transCost_map.find(make_pair(i, j))->second;
            facility_dist_vector.emplace_back(j, dist);
         }

         sort(facility_dist_vector.begin(), facility_dist_vector.end(), pair_cmp);

         s_order_map.emplace(i, facility_dist_vector);
     }

     auto it = this->solution_order_map.find(solution_index);

     if(it != this->solution_order_map.end()){
         it->second = s_order_map;
     }else{
         this->solution_order_map.emplace(solution_index, s_order_map);
     }
}

void EAMLS::get_all_solution_order_map() {
    for(const auto & s_it: pop){
        this->readjust_single_solution_order(s_it.first);
    }
}

double EAMLS::calculate_fitness(vector<unsigned char> &solution, double alpha, int m) {
    double fitness = 0;
    for(int i=0; i<solution.size(); i++){
        auto site_it = this->m_dataLoader.site_info_map.find(i);
        fitness += site_it->second.fixed_cost * solution[i];

    }
    return 1/fitness;
}