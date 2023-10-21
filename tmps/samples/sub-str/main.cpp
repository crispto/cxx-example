#include <iostream>

int main(int, char**) {
    std::string name = "004866.pcd";
    size_t pos = name.find_last_of(".");
    printf("Pos is %d\n", pos);
    if (pos == name.size() - 4 && std::string(name.substr(pos)) == ".pcd"){
        printf("errro\n");
    }
    std::string ext = name.substr(pos + 1);
    std::cout <<"ext is " << ext << std::endl;
    printf("ext is %s, pos::nopos is %d\n", ext.c_str(), name.npos);

}
