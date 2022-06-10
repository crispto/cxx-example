#include "jupyter.h"
#include <iostream>

Jupyter *start()
{
    Jupyter *j = new Jupyter();
    return j;
}

int stop(Jupyter *j)
{
    std::cout << "this do nothing" << std::endl;
    return 0;
}