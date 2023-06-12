#include <iostream>

// typedef bool (*compare)(int i, int j);
using namespace std;

int main()
{
   using person = struct {
        int age;
        string name;
        void show(){
                printf("age: %d, name: %s\n", age, name.c_str());
        }
   };

   person k{12, "yang"};
   k.show();

return 0;
}