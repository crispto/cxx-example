#include <iostream>
#include "dirent.h"
#include <vector>
#include <algorithm>

int main(){
    std::string base_path = "/home/SENSETIME/yangchengwei/data/4v2l/50";

    //list all files in directory
    DIR *dir;
    struct dirent *ent;
    int most_wante = 100000;
    int get_count = 0;
    std::vector<std::string> files;
    if ((dir = opendir(base_path.c_str())) != NULL){
        while((ent = readdir(dir)) != NULL && get_count++ < most_wante){
            files.emplace_back(ent->d_name);

        }
        closedir(dir);
    }else{
        throw("open dir failed");
    }
    std::sort(files.begin(), files.end());
    for (size_t i = 0; i< 10;i++){
        std::cout << files[i] << std::endl;
    }
    std::cout <<"data count " << files.size() << std::endl;
    


}