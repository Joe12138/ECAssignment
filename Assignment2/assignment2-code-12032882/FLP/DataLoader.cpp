//
// Created by neighborhood_lan on 2021/3/30.
//

#include <fstream>
#include "DataLoader.h"

DataLoader::DataLoader(const string& file_path) {
    read_file(file_path);
//    cout << "Test" << endl;
}

void DataLoader::read_file(const string &file_path) {
    ifstream file_content(file_path);

    string line_content;
    int line_num = 1;
    vector<string> split_result;
    while (getline(file_content, line_content)){
//        cout << line_content << endl;
        if(line_num == 1){
            DataLoader::split_str(line_content, "=", split_result);
            this->site_num = stoi(split_result[1]);
            split_result.clear();
        }else if(line_num == 8){
            DataLoader::split_str(line_content, "=", split_result);
            this->fail_prob = stod(split_result[1]);
            split_result.clear();
        }else if(line_num>=10 && line_num<=10+this->site_num-1){
            DataLoader::split_str(line_content, ",", split_result);
            int site_index = stoi(split_result[0]);
            double x_coordinate = stod(split_result[1]);
            double y_coordinate = stod(split_result[2]);
            SITE_INFO site;
            site.x_coordinate = x_coordinate;
            site.y_coordinate = y_coordinate;
            this->site_info_map.emplace(site_index, site);
            split_result.clear();
        }else if (line_num>=10+this->site_num+1 && line_num<=10+this->site_num*2){
            DataLoader::split_str(line_content, ",", split_result);
            int site_index = stoi(split_result[0]);
            int demand = stoi(split_result[1]);

            auto s_it = this->site_info_map.find(site_index);
            s_it->second.demand = demand;
            split_result.clear();
        }else if(line_num>=10+this->site_num*2+2 && line_num<=10+this->site_num*3+1){
            DataLoader::split_str(line_content, ",", split_result);
            int site_index = stoi(split_result[0]);
            int fixed_cost = stoi(split_result[1]);
            auto s_it = this->site_info_map.find(site_index);
            s_it->second.fixed_cost = fixed_cost;
            split_result.clear();
        }else if(line_num >= 10+this->site_num*3+3){
            DataLoader::split_str(line_content, ",", split_result);
            int start_index = stoi(split_result[0]);
            int end_index = stoi(split_result[1]);
            double trans_cost = stod(split_result[2]);

            this->site_transCost_map.emplace(make_pair(start_index, end_index), trans_cost);
            split_result.clear();
        }
//        cout << line_content << endl;
        line_num += 1;
    }
}

void DataLoader::split_str(const string &str, const string &pattern, vector<string> &result) {
    string::size_type str_size = str.size();
    string::size_type pos;
    for(string::size_type i=0; i<str_size; i++){
        pos = str.find(pattern, i);
        if(pos < str_size){
            string sub_str = str.substr(i, pos-i);
            result.push_back(sub_str);
            i = pos + pattern.size()-1;
        }else if(pos==string::npos){
            result.push_back(str.substr(i, str_size));
            break;
        }
    }
}
