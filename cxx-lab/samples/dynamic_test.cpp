#include <iostream>
#include <memory>
using namespace std;
typedef struct plugin_t{
  std::string name;
  int age;
};

auto_ptr<plugin_t> get_plugin(){
  plugin_t *v= new plugin_t();
  auto_ptr<plugin_t> pt(v);
  pt-> name = "yangchengwei";
  return pt;
}

int main(){
  auto_ptr<plugin_t> a = get_plugin();
  std::cout << "name is " << a->name << std::endl;
}