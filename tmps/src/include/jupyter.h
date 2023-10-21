#ifndef JUPYTER_HEADER__
#define JUPYTER_HEADER__

#include <iostream>
class Jupyter {
  public:
    Jupyter() { std::cout << "jupyter is construcing " << std::endl; };
    ~Jupyter() { std::cout << "jupyter is unconst..." << std::endl; };
};

Jupyter *start();
int stop();
#endif