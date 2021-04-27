//
// Created by Joe Lan on 2021/4/25.
//

#ifndef FLP_BRUTEFORCE_H
#define FLP_BRUTEFORCE_H
#include "EAMLS.h"

class BruteForce {
private:
    DataLoader dataLoader;
    EAMLS eamls;
public:
    explicit BruteForce(DataLoader & dataLoader1, EAMLS & eamls1);
};


#endif //FLP_BRUTEFORCE_H
