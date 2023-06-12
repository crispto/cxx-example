#include "co/log.h"
#include <iostream>
int main(int argc, char** argv) {

    std::cout  <<  FLG_min_log_level << std::endl;
    flag::parse(argc, argv);

    TLOG("xx") << "s" << 23; // topic log
    DLOG << "hello " << 23;  // debug
    LOG << "hello " << 23;   // info
    WLOG << "hello " << 23;  // warning
    ELOG <<"ERROR " << 2112;
    FLOG << "hello " << 23;  // fatal

    return 0;
}