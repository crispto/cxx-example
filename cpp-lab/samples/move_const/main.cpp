#include "iostream"

/* vector 的 iter 构造是否是 move 的

/  g++ -fsanitize=address -g ./main.cpp -o main
    结论： vec  的 iter 构造方式并不是 move 的，而是 copy 的
*/

#include <vector>

using namespace std;
int main(){

    int * arr = new int[3];
    for (int i = 0; i <3;i++){
        arr[i] = 100+i;
    }
    std::vector<int> vec1(arr,arr+3);

    for (auto &&x : vec1){
        cout <<x <<endl;
    }
    vec1.clear();
    // delete[] arr;
}