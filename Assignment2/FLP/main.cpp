#include <iostream>
#include <fstream>
#include "DataLoader.h"
#include "EAMLS.h"
#include <unistd.h>
#include <chrono>

#define seed_num 19491001

typedef struct parameter{
    int pop_size;
    double mutation_size;
    int n;
    double beta;
    int step_size;
    int generation_number;
    int instance_num;
}PARAMETER;

int main() {
    PARAMETER ten_instance = {
            20,
            0.1,
            10,
            0.8,
            100,
            10,
            8
    };

    PARAMETER thirty_instance = {
            20,
            0.1,
            10,
            0.8,
            100,
            15,
            8
    };

    PARAMETER fifty_instance = {
            20,
            0.1,
            10,
            0.8,
            100,
            20,
            8
    };

    PARAMETER seventy_instance = {
            20,
            0.1,
            10,
            0.8,
            100,
            25,
            8
    };

    PARAMETER hundred_instance = {
            100,
            0.1,
            10,
            0.8,
            100,
            50,
            8
    };

    PARAMETER six_hundred_instance = {
            200,
            0.1,
            10,
            0.8,
            100,
            250,
            4
    };

    unordered_map<int, PARAMETER> site_num_parameter_map = {
            {10,  ten_instance},
//            {30, thirty_instance},
            {50,  fifty_instance},
            {100, hundred_instance},
//            {70, seventy_instance},
            {600, six_hundred_instance}
    };

    string file_name = R"(G:\EvolutionaryAlgorithm\ECAssignment\Assignment2\FLP\Result\Total\10_init_False_)" + to_string(time(nullptr)) + ".csv";
    ofstream f;
    f.open(file_name);
    f.close();

    fstream f1;
    f1.open(file_name, ios::out);

    for(const auto & it: site_num_parameter_map){
        string file_path_part = R"(G:\EvolutionaryAlgorithm\ECAssignment\Assignment2\FLP\Instance\)";
        f1 << "num_site = " << it.first << "neighborhood_lan = False" << endl;

        vector<double> zhang_fit_vector;
        vector<double> lan_fit_vector;


        for(int i=0; i<it.second.instance_num; i++){
            cout << it.first << " sites, instance " << i << endl;
            string file_path = to_string(it.first)+"_"+to_string(i)+".txt";
//            cout << file_path_part+file_path << endl;
            DataLoader dataLoader = DataLoader(file_path_part+file_path);
            int repeat_num = 30;
            vector<double> objective_value_vector;
            vector<int> num_repair_vector;
//            vector<double> average_obj;
//            vector<double> best_obj;
            double total_zhang_fit = 0;
            double total_lan_fit = 0;
            for(int j=0; j<repeat_num; j++){
//                cout << "Repeated Number = " << j << endl;
                EAMLS eamls = EAMLS(dataLoader, it.second.pop_size);
                eamls.instance_num = i;
//                double objective_value = eamls.EA_with_MLS(it.second.generation_number, it.second.mutation_size, it.second.beta,
//                                                               it.second.step_size, it.second.n);
//                eamls.init_pop_lan(eamls.pop_size, eamls.num_site);
//                eamls.evaluate_pop(eamls.pop, eamls.index_fitness_map, eamls.alpha_value);
//
//                double total_obj = 0;
//                double b_obj = INT32_MAX;
//                for(auto a: eamls.index_fitness_map){
//                    total_obj += 1/a.second;
//                    if(1/a.second < b_obj){
//                        b_obj = 1/a.second;
//                    }
//                }
//
//                average_obj.emplace_back(total_obj/eamls.pop_size);
//                best_obj.emplace_back(b_obj);

                vector<unsigned char> solution;
                for(int kk=0; kk<it.first; kk++){
                    solution.emplace_back(0);
                }
                default_random_engine generator(clock());
                uniform_int_distribution<unsigned int> one_dist(0, solution.size()-1);
                solution[one_dist(generator)] = 1;

                vector<unsigned char> zhang_solution = solution;
                eamls.repair_strategy(zhang_solution, 1);

                double zhang_fit = eamls.calculate_fitness(zhang_solution, 1, false, -1);
//                zhang_fit_vector.emplace_back(1/zhang_fit);
                total_zhang_fit += 1/zhang_fit;

                vector<unsigned char> lan_solution = solution;
                eamls.repair_strategy_lan(lan_solution, 1);
                double lan_fit = eamls.calculate_fitness(lan_solution, 1, false, -1);
//                lan_fit_vector.emplace_back(1/lan_fit);
                total_lan_fit += 1/lan_fit;
//                cout << 1/zhang_fit << "; " << 1/lan_fit << endl;

//                objective_value_vector.emplace_back(objective_value);
                num_repair_vector.emplace_back(eamls.num_repair_operation);
//                sleep(1);
//                break;
//                break;
            }
            zhang_fit_vector.emplace_back(total_zhang_fit/30);
            lan_fit_vector.emplace_back(total_lan_fit/30);
            string content = "Instance" + to_string(i) + ",";
            for(double k: objective_value_vector){
                content += to_string(k) + ",";
            }
            f1 << content << endl;
//            string avg_content = "Instance_"+ to_string(i)+"_avg"+",";
//            for (double k: average_obj) {
//                avg_content += to_string(k) + ",";
//            }
//            f1 << avg_content << endl;
//
//            string best_content = "Instance_"+ to_string(i)+"_best"+",";
//            for (double k: best_obj) {
//                best_content += to_string(k) + ",";
//            }
//            f1 << best_content << endl;

//            int total_num = 0;
//            for(int km: num_repair_vector){
//                total_num += km;
//            }
//            cout << total_num/30 << endl;
//            break;
        }
//        break;
        f1 << endl;
        for(double z: zhang_fit_vector){
            cout << z << "," << endl;
        }

        cout << "Lan" << endl;
        for(double l: lan_fit_vector){
            cout << l << "," << endl;
        }
    }
    f1.close();
    return 0;
}




