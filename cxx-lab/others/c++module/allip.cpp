#include <iostream>
#include <vector>


using namespace std;
/*
string gen_ip(vector<string> &tmp){
    string s = tmp[0];
    for (size_t i = 1; i< tmp.size();i++){
        s+=".";
        s+=tmp[i];
    }
    return s;
}
void dfs(char *ptr, vector<string> &tmp, vector<string> &ips){
    if(*ptr == '\0') return;
    if(tmp.size() == 4 || *ptr == '\0'){
        if (tmp[0][0] != '0'){
            ips.emplace_back(gen_ip(tmp));
        }
    }
    for (size_t i =1; i< 4;i++){
        if(ptr +i -1 == '\0') break;
        char tmp[i+1];
        memcpy(tmp, ptr, i);
        tmp[i] = '\0';
        string v(tmp);
        if (to_int(v) < )


    }

}
*/
int main(){
    cout <<"hello owrldl" <<endl;
}