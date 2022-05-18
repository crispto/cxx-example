#include <iostream>
#include "common.hpp"

using namespace std;
int main()
{
  string name = "yang";
  string out = "";
  echo(name, out);
  cout << "output is " << out << endl;
}
