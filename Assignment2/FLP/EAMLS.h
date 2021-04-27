//
// Created by lan on 2021/3/30.
//

#ifndef FLP_EAMLS_H
#define FLP_EAMLS_H
#include "DataLoader.h"
#include <random>
#include <vector>
#include <ctime>
#include <cmath>
#include <unordered_set>

class EAMLS {
    // alpha = 1
private:
    // population
    unordered_map<int, vector<unsigned char> > pop;
    // solution and its corresponding facility number
//    unordered_map<int, int> index_m_map;
    // solution index and its corresponding fitness
    unordered_map<int, double> index_fitness_map;
    // solution and its corresponding facility order for each customer
    unordered_map<int, unordered_map<int, vector<pair<int, double> > > > solution_order_map;
    DataLoader m_dataLoader;
    int pop_size;
    int num_site;
    double alpha_value = 1.0;


    struct vector_hash{
        size_t operator()(const vector<unsigned char> & v) const{
            hash<unsigned char> hasher;
            size_t seed = 0;

            for(unsigned char i: v){
                seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
            }

            return seed;
        }
    };

public:
    bool lan = false;
    bool change_init = true;
    int instance_num = 0;
    EAMLS(DataLoader &dataLoader, int p_size);
    void init_pop(int p_size, int n_site);
    void init_pop_lan(int p_size, int n_site);
    void random_vector(int n_site, int m_value, unordered_set<unsigned int> &random_vec);
    double calculate_fitness(const vector<unsigned char> &solution, double alpha, bool symbol, int solution_index);
    int readjust_single_solution_order(const vector<unsigned char> &solution,
                                       unordered_map<int, vector<pair<int, double> > > &s_order_map);
//    void get_all_solution_order_map();

    static bool pair_cmp_big(const pair<int, double> &x, const pair<int, double> &y);
    static bool pair_cmp_small(const pair<int, double> &x, const pair<int, double> &y);
    static bool fixed_cost_cmp(const pair<int, int> &x, const pair<int, int> &y);

    void mutation(double mutation_rate, unordered_map<int, vector<unsigned char> >& new_pop);

    void evaluate_pop(unordered_map<int, vector<unsigned char>> &population,
                      unordered_map<int, double> &solution_index_fitness_map, double alpha);

    static int check_constraint(vector<unsigned char> & solution);

    void repair_strategy(vector<unsigned char> & solution, int m_value);

    void repair_strategy_lan(vector<unsigned char> & solution, int m_value);

    double calculate_virtual_fitness(int facility_index);

    void get_all_neighbor(const vector<unsigned char> & solution,
                          unordered_set<vector<unsigned char>, vector_hash > & neighbor_set);

    void memorable_local_search(unordered_map<int, vector<unsigned char>> &parent_pop,
                                       unordered_map<int, vector<unsigned char>> &mutation_pop, int n,
                                       unordered_set<vector<unsigned char>, vector_hash> &ind_local_search,
                                       unordered_map<int, double> &parent_index_fitness_map,
                                       unordered_map<int, double> &mutation_index_fitness_map,
                                       unordered_set<vector<unsigned char>, vector_hash> &ls_offspring);

    double EA_with_MLS(int generation_num, double mutation_rate, double beta, int step_size, int n);

    double get_l3_value(unordered_map<int, vector<unsigned char> > & pop_after_selection,
                        unordered_set<vector<unsigned char>, vector_hash> &all_neighbor_inds) const;

    void survival_selection(unordered_map<int, vector<unsigned char>> &mutation_pop,
                            unordered_set<vector<unsigned char>, vector_hash> &ls_pop,
                            unordered_map<int, double> &mutation_index_fitness_map, double alpha);

    void neighbor_search(vector<unsigned char> & solution,
                         unordered_set<vector<unsigned char>, vector_hash>& neighbor_set);
};


#endif //FLP_EAMLS_H
