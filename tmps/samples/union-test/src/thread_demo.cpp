#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <math.h>
// 使用 3 个线程来计算 N 以内的素数

double single_thread(int n)
{
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

using callback = void (*)(double *total, double count, std::mutex &mtx);

void process(int thread_id, int block_dim, int n, double *total, std::mutex &mtx, callback cb)
{
    double count = 0;
    int i = 0;
    while (true) {
        int start = i * block_dim + thread_id;
        if (start >= n) {
            break;
        }
        count += sqrt(start);
        i++;
    }
    cb(total, count,mtx);
}


int64_t get_mili_now(){
  auto now = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}

void fn(double *total, double count, std::mutex &mtx) {
    std::lock_guard<std::mutex> g(mtx);
    *total += count;
};

int main()
{


    std::mutex mtx;
    double total = 0;

    int N = 1000000000;
    int block_dim = 10;
    int64_t start = get_mili_now();
    // 单线程
    double cnt = single_thread(N);
    std::cout << "单线程的结果是 " << cnt << \
    "时间 " << get_mili_now()-start << "ms" << std::endl;
    std::vector<std::thread> threads;
    for (int i = 0; i < block_dim; i++) {
        threads.emplace_back(process, i, block_dim, N, &total, std::ref(mtx), fn);
    }


    for (auto &&t : threads){
      t.join();
    }
    std::cout << "多线程的结果是 " << total << ", 时间 " << get_mili_now()-start << "ms" << std::endl;
    return 0;
}
