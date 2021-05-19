#include <iostream>
#include <fstream>
#include "DataLoader.h"
#include "EAMLS.h"
#include <unistd.h>
#include <chrono>

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
//            {10,  ten_instance}
//            {30, thirty_instance}
            {50,  fifty_instance}
//            {100, hundred_instance}
//            {70, seventy_instance}
//            {600, six_hundred_instance}
    };

    string file_name = R"(E:\2021_spring\Evolutional Computing\ECAssignment\Assignment2\FLP\Result\Total\50_Neighbor_True_)" + to_string(time(nullptr)) + ".csv";
    ofstream f;
    f.open(file_name);
    f.close();

    fstream f1;
    f1.open(file_name, ios::out);

    for(const auto & it: site_num_parameter_map){
        string file_path_part = R"(E:\2021_spring\Evolutional Computing\ECAssignment\Assignment2\FLP\Instance\)";
        f1 << "num_site = " << it.first << "neighborhood_lan = False" << endl;
        for(int i=0; i<it.second.instance_num; i++) {
            cout << it.first << " sites, instance " << i << endl;
            string file_path = to_string(it.first) + "_" + to_string(i) + ".txt";
//            cout << file_path_part+file_path << endl;
            DataLoader dataLoader = DataLoader(file_path_part + file_path);
            int repeat_num = 30;
            vector<double> objective_value_vector;
            for (int j = 0; j < repeat_num; j++) {
//                cout << "Repeated Number = " << j << endl;
                EAMLS eamls = EAMLS(dataLoader, it.second.pop_size);
                eamls.instance_num = i;
                double objective_value = eamls.EA_with_MLS(it.second.generation_number, it.second.mutation_size,
                                                           it.second.beta,
                                                           it.second.step_size, it.second.n);
                objective_value_vector.emplace_back(objective_value);
                if (it.first == 10) {
                    sleep(1);
                }
            }
            string content = "Instance" + to_string(i) + ",";
            for (double k: objective_value_vector) {
                content += to_string(k) + ",";
            }
            f1 << content << endl;
        }
        f1 << endl;
    }
    f1.close();
    return 0;
}
