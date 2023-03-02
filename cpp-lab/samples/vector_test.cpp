#include "common.hpp"
using namespace std;
#include <chrono>
#include <thread>

int test_vec()
{
    vector<int> v(10, 1);
    display_vec(v);

    map<int, int> m;
    for (int i = 0; i < 10; i++) {
        m[i] = 2 * i;
    }
    display_map(m);
    return 0;
}
void test_call()
{
    for (int i = 0; i < 10; i++) {
        cam_param_t v = call_counter();
        std::cout << "x " << v.x << " y: " << v.y << "yaw: " << v.yaw << std::endl;
    }
}

void accept_string(const std::string &input)
{
    std::cout << "input is " << input << std::endl;
};

void accept_char(const char *input)
{
    accept_string(std::string(input));
}

void test_getstring()
{
    std::string input = "hello";
    char *out = get_char_array(input);
    std::cout << "out is  " << out << std::endl;
    std::cout << "len of the str is " << strlen(out) << std::endl;
    delete[] out;
}

void test_getstring2()
{
    std::string input = "hello";

    char out[1025];
    int ret = get_char_array2(input, out);
    if (ret < 0) {
        std::cout << "error" << std::endl;
        return;
    }
    std::cout << "out is " << out << "\nlen of out is " << strlen(out) << std::endl;
}
int test3()
{
    const char *v = "yangcheng";
    accept_char(v);
    return 0;
}
class Tmp
{
    public:
    Tmp()
    {
        std::cout << "tmp create" << std::endl;
    }
    ~Tmp()
    {
        std::cout << "tmp destory" << std::endl;
    }
    void yaw()
    {
        std::cout << "yaw" << std::endl;
    }
};
int test_scope()
{
    {
        Tmp a;
    }
    this_thread::sleep_for(chrono::seconds(1));
    cout << "endof test_scope" << std::endl;
}
#include <random>

string minNumber(vector<int>& nums) {
    std::sort(nums.begin(), nums.end(), [](int i , int j ){
        string v1 = to_string(i) +to_string(j);
        string v2 = to_string(j) +to_string(i);
        cout <<"v1 v2" <<v1 <<", " <<v2 <<endl;
        return v1.compare(v2) <0 ;
        });
    string ret = "";
    for(auto & k : nums){
        ret += to_string(k);
    }
    return ret;
}
int main()
{
   vector<int> nums = {3,30,34,5,9};
   string k = minNumber(nums);
   cout <<k <<endl;
   string  v1 = "330";
   string v2 = "303";

   cout <<v1.compare(v2) <<endl;

    return 0;
}