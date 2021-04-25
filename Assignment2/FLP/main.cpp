#include <iostream>
#include "DataLoader.h"
#include "EAMLS.h"

int main() {
    const string file_path = R"(E:\2021_spring\Evolutional Computing\ECAssignment\Assignment2\FLP\Instance\50_0.txt)";
    DataLoader dataLoader = DataLoader(file_path);
    int pop_size = 20;
    double mutation_rate = 0.1;
    double beta = 0.8;
    int n = 10;
    int step_size = 20;
    EAMLS eamls = EAMLS(dataLoader, pop_size);
    eamls.EA_with_MLS(100, mutation_rate, beta, step_size, n);
    return 0;
}
