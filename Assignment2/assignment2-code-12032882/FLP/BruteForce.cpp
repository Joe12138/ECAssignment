//
// Created by Joe Lan on 2021/4/25.
//

#include "BruteForce.h"

BruteForce::BruteForce(DataLoader & dataLoader1, EAMLS & eamls1): dataLoader(dataLoader1), eamls(eamls1) {
    int num_site = this->dataLoader.site_num;
    int m = 3;
    unsigned char one = 1;
    unsigned char zero = 0;

    double max_fitness = 0;
    for(int i=0; i<num_site-1; i++){
        for (int j = i+1; j < num_site-0; j++) {
//            for(int z=j+1; z<num_site; z++){
                vector<unsigned char> solution;
                for(int k=0; k<num_site; k++){
                    if(k==i || k==j){
                        solution.emplace_back(one);
                    }else{
                        solution.emplace_back(zero);
                    }
                }

                double fitness = this->eamls.calculate_fitness(solution, 1, false, -1);
                if(fitness > max_fitness){
                    max_fitness = fitness;
                }

                for(auto l: solution){
                    cout << (int)l << ",";
                }
                cout << endl;
                cout << "fitness" << fitness << endl;
//            }

            }


    }

    cout << 1/max_fitness;
}