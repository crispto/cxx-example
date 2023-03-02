#include <iostream>
#include <map>

int main(){
  std::map<std::string, int> a;
  int j = a["yang"];
  std::cout << "j is " << j << std::endl;
  return 0;
}