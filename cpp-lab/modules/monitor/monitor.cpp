#include <iostream>
#include <vector>
#include <thread>
#include <map>
#include <chrono>
#include <random>
#include <mutex>
#include <sys/types.h>
#include <unistd.h>
#include <memory>
#include <stack>
#include <algorithm>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/sysinfo.h"
#include "sys/times.h"
#include "sys/types.h"



#define TIMMING(flag) Timer __timerp(flag)

class Monitor
{
public:
    struct metric {
        float mem;
        float gpu;
        float cpu;
        int64_t ts; // 采样时间戳
    };
    Monitor(int iterval_milli);
    ~Monitor();
    // thread safe
    void Start(std::string flag);
    void End(std::string flag);
    void report(bool time, bool resource);

private:
    std::mutex monitor_mutex_;
    struct func_proc {
        std::string flag;
        int64_t start_time;
        int64_t end_time;
    };
    // 自动隔 inter
    void run();
    float prob_mem();
    float prob_gpu();
    float prob_cpu();

private:
    bool exit_ = false;
    bool started_ = false;
    int iterval_milli_;
    std::thread monitor_thread_;
    std::map<int, std::stack<func_proc>> resource_stack_; // thread id -> func_proc
    std::map<int, std::vector<func_proc>> func_proc_map_; // thread id -> func_proc
    std::vector<metric> resouce_;
};
static std::unique_ptr<Monitor> monitor_g(new Monitor(1000));
class Timer
{
public:
    Timer(std::string flag) : _flag(flag)
    {
        monitor_g->Start(flag);
    };
    ~Timer()
    {
        monitor_g->End(_flag);
    };

private:
    std::string _flag;
};

Monitor::Monitor(int interv_milli) : iterval_milli_(interv_milli)
{
    monitor_thread_ = std::thread(&Monitor::run, this);
}
Monitor::~Monitor()
{
    exit_ = true;
    if (monitor_thread_.joinable()) {
        monitor_thread_.join();
    }
}

void Monitor::report(bool time, bool resource)
{
    std::lock_guard<std::mutex> lock(monitor_mutex_);

    std::cout << "report" << std::endl;
    if (time) {

        for (auto &item : func_proc_map_) {
            std::cout << "thread id: " << item.first << std::endl;
            for (auto &func : item.second) {
                std::cout << "flag: " << func.flag << " start: " << func.start_time
                          << " end: " << func.end_time << " elapse "
                          << func.end_time - func.start_time << "ms" << std::endl;
            }
        }
    }
    if (resource) {

        for (auto &item : resouce_) {
            std::cout << "ts: " << item.ts << " cpu: " << item.cpu << " gpu: " << item.gpu
                      << " mem: " << item.mem << std::endl;
        }
    }
}
static int64_t get_now_milli()
{
    auto now = std::chrono::high_resolution_clock::now();
    int64_t epoch =
        std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return epoch;
}

void Monitor::Start(std::string flag)
{
    int thread_id = getpid();
    func_proc tmp;
    tmp.flag = flag;
    tmp.start_time = get_now_milli();
    resource_stack_[thread_id].push(tmp);
}

void Monitor::End(std::string flag)
{
    int thread_id = getpid();
    func_proc tmp = resource_stack_[thread_id].top();
    if (tmp.flag != flag) {
        throw("flag not match");
    }
    tmp.end_time = get_now_milli();
    resource_stack_[thread_id].pop();
    func_proc_map_[thread_id].push_back(tmp);
}

void Monitor::run()
{
    while (!exit_) {
        int64_t now = get_now_milli();
        Monitor::metric m;
        m.ts = now;
        m.cpu = prob_cpu();
        m.gpu = prob_gpu();
        m.mem = prob_mem();
        resouce_.push_back(m);
        std::this_thread::sleep_for(std::chrono::milliseconds(iterval_milli_));
    }
}



static int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}
/// 获取当前 cpu 使用率
double get_current_cpu_usage()
{
    struct tms timeSample {
    };
    clock_t now;
    double percent;

    now = times(&timeSample);
    if (now <= lastCPU || timeSample.tms_stime < lastSysCPU || timeSample.tms_utime < lastUserCPU) {
        // Overflow detection. Just skip this value.
        percent = -1.0;
    } else {
        percent = (timeSample.tms_stime - lastSysCPU) + (timeSample.tms_utime - lastUserCPU);
        percent /= (now - lastCPU);
        percent /= numProcessors;
        percent *= 100;
    }
    lastCPU = now;
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;

    return percent;
}

} // namespace


int getValue(){ //Note: this value is in KB!

}

float Monitor::prob_cpu()
{
    return 0;
}

float Monitor::prob_gpu()
{
    return 0;
}

float Monitor::prob_mem()
{
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int process_children()
{
    TIMMING("process_children");
    int rd = rand() % 10 + 10; // [500, 1000] ms
    std::this_thread::sleep_for(std::chrono::milliseconds(rd));
    return 0;
}

int process()
{
    TIMMING("process");

    int rd = rand() % 20 + 10; // [500, 1000] ms
    process_children();
    std::this_thread::sleep_for(std::chrono::milliseconds(rd));
    return 0;
}

int main(int, char **)
{
    for (int i = 0; i < 100; i++) {
        process();
    }
    monitor_g->report(false, true);
}
