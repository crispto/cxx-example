#define LOG_MODULE_ID "log_main"
#include <iostream>
#include <string>

#include <tbox/base/log.h>
#include <tbox/base/log_output.h>
using namespace std;

int main()
{
    LogOutput_Enable();

    LogInfo("this log print in C++ file");

    return 0;
}
