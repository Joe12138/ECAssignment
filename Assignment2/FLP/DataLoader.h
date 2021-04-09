//
// Created by lan on 2021/3/30.
//

#ifndef FLP_DATALOADER_H
#define FLP_DATALOADER_H
#include <iostream>
#include <unordered_map>

using namespace std;

class DataLoader {
    typedef struct site_info{
        double x_coordinate;
        double y_coordinate;
        int demand;
        int fixed_cost;
    }SITE_INFO;

    struct pair_hash{
        template<class T1, class T2>
                std::size_t operator()(const std::pair<T1, T2>& p) const{
                    auto h1 = std::hash<T1>{}(p.first);
                    auto h2 = std::hash<T2>{}(p.second);
                    return h1^h2;
                }
    };

    int site_num;
    double fail_prob;
    unordered_map<int, SITE_INFO > site_info_map;
    unordered_map<pair<int, int>, double, pair_hash> site_transCost_map;


};


#endif //FLP_DATALOADER_H
