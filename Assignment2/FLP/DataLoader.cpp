//
// Created by lan on 2021/3/30.
//

#include <fstream>
#include "DataLoader.h"

DataLoader::DataLoader(const string& file_path) {
    read_file(file_path);
}

void DataLoader::read_file(const string &file_path) {
    ifstream file_content(file_path);

    string line_content;
    int line_num = 1;
    while (getline(file_content, line_content)){
        if(line_num == 1){

        }
        cout << line_content << endl;
        line_num += 1;
    }
}
