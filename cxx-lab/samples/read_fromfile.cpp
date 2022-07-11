#include <iostream>
#include <fstream>
#include <string>

int main(){
  std::fstream f("param.json");
  if (!f.is_open()){
    std::cout <<"not open !! " << std::endl;
    return 0;
  }
  const char * data = "";
  std::string vstr{std::istreambuf_iterator<char> (f), std::istreambuf_iterator<char>()};
  std::cout <<"get v " << vstr << " v.size " << vstr.size() << std::endl;
  data = vstr.c_str();
  std::cout << "data " << data << std::endl;
  return 0;

}