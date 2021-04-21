//
// Created by lan on 2021/3/30.
//

#ifndef FLP_EAMLS_H
#define FLP_EAMLS_H
#include "DataLoader.h"
#include <random>
#include <vector>
#include <ctime>

class EAMLS {
private:
    // population
    unordered_map<int, vector<unsigned char> > pop;
    // solution and its corresponding facility number
    unordered_map<int, int> index_m_map;
    // solution and its corresponding facility order for each customer
    unordered_map<int, unordered_map<int, vector<pair<int, double> > > > solution_order_map;
    DataLoader m_dataLoader;
    int pop_size;
    int num_site;

public:
    EAMLS(DataLoader &dataLoader, int p_size);
    void init_pop(int p_size, int n_site);
    double calculate_fitness(vector<unsigned char> &solution, double alpha, int m);
    void readjust_single_solution_order(int solution_index);
    void get_all_solution_order_map();

    static bool pair_cmp(const pair<int, double> &x, const pair<int, double> &y);
};


#endif //FLP_EAMLS_H
