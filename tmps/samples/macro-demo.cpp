#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sstream>
#include <vector>

#define SEPRATOR '\n'

// 原本想探究一下 string(char*) 是移动构造还是复制构造
// 这个函数会导致内存泄露
template <typename... Args> std::string format_string_leak(std::string &&format, Args... elems)
{
    char *p = new char[1024];
    sprintf(p, format.c_str(), elems...);
    return std::string{ p }; // 这里会发生转移吗？实际是不会，这里会发生复制
}

// 正确的用法
template <typename... Args> std::string format_string(std::string &&format, Args... elems)
{
    char *p = new char[1024];
    sprintf(p, format.c_str(), elems...);
    std::string ret{ p }; // 这里会发生转移吗？实际是不会，这里会发生复制
    delete[] p;
    return ret;
}

// 打印资源使用情况，这里只打印内存
void printResource()
{
    std::string cmd = format_string("ps -p %d -o rss", getpid());
    FILE *pipe = popen(cmd.c_str(), "r"); // 这里开启了一个管道命令
    if (!pipe) {
        std::cerr << "pipline create failed" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        // 通过重复读取的方式将管道文件中的内容读取出来，有没有更简单优雅的方法？
        std::stringstream ss;
        char buf[128];
        while (fgets(buf, sizeof(buf), pipe) != nullptr) {
            ss << buf;
        }
        // 管道输出为该进程的常驻内存占用(kb)，要按行解析找到第二行
        //  RSS
        // 73893
        std::vector<std::string> result;
        std::string token;
        while (std::getline(ss, token, SEPRATOR)) {
            result.emplace_back(token);
        }

        int mem_usage_kb = std::stoi(result[1]);
        std::cout << format_string("mem usage : %dkb\n", mem_usage_kb);
        pclose(pipe); // 如果没有这个，就会发生内存泄露
    }
}
// 编译 g++ --std=c++11 ./main.cpp -o main
// 模拟泄露 ./main 1000 --leak true
// 正常  ./main 10000
int main(int argc, char *argv[])
{
    int bench_count = 1;
    bool leak = false;

    if (argc >= 2) {
        bench_count = std::stoi(argv[1]);
    }
    if (argc == 4 && std::string(argv[2]) == "--leak") {
        leak = std::string(argv[3]) == "true" ? true : false;
    }
    std::cout << "test leak " << (leak ? "true" : "false") << std::endl;
    // 重复跑，不断打印内存使用，看是否有上涨
    for (int i = 0; i < bench_count; i++) {
        if (leak) {
            std::string v = format_string_leak("hello world %s, %d, %ld", "yang", 12, 23.L);
        } else {
            std::string v = format_string("hello world %s, %d, %ld", "yang", 12, 23.L);
        }
        if (i % 20 == 0) {
            printResource();
        }
    }
    return 0;
}