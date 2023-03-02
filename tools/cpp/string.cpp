#include <stdarg.h>
#include <iostream>
using namespace std;

string format(const char *format, ...){

    va_list args;
    va_start(args, format);
    char buf[512];
    int len = vsnprintf(buf, 512,format, args);
    cout <<"Len is " << len <<endl;
    buf[len] ='\0';
    va_end(args);
    return string(buf);
}

int main(){
    // char a = INT_TO_CHAR(1);
    // cout <<"a is " <<a<<endl;
    string a = format("name: %s, age:%d, address: %s", "yang", 12, "jiangxi");
    cout <<"a is " << a <<endl;
    return 0;
}