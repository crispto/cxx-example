#include <iostream>
using namespace std;


static void _check(int val, const char * fun, const char* file, int line){
        cout << "val " << val << endl;
        cout << "fun " << fun << endl;
        cout << "file " << file << endl;
        cout << "line " << line << endl;
        

}
#define checkErrors(val) _check((val), (#val), __FILE__, __LINE__)


int get_int(){
        return 10;
}

int main(){

        checkErrors(get_int());
        return 0;
}