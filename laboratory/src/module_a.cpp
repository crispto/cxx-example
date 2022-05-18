#include "common.hpp"
#include <string>

typedef int k_err;

k_err echo(std::string v, std::string& out){
  if (v.size() == 0){
    return -1;
  }
  out = v + " word";
  return 0;
}