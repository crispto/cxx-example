#ifndef __SYSTEM_TIME__
#define __SYSTEM_TIME__
#include <string>

// 生成类似于2023-10-22 00:45:27
std::string get_time_now_str(const char *format_str = "%F %H:%M:%S")
{
    char timestamp_str_[20];
    time_t now = time(nullptr);
    struct tm *tm = localtime(&now);
    strftime(timestamp_str_, sizeof(timestamp_str_), format_str, tm);
    return std::string(timestamp_str_);
}

#endif
