#include <iostream>
#include <string>

#include <tbox/base/log.h>
#include <tbox/base/log_output.h>
using namespace std;

extern "C" void DoSomeThing();

int main()
{
    LogOutput_Enable();

    LogInfo("this log print in C++ file");
    DoSomeThing();

    return 0;
}
