#include <iostream>
#include <math.h>
#include <time.h>
#include <utility>
#include <vector>
#include <thread>
#include <mutex>

#define NUMS 10240
using namespace std;

vector<pair<double, double>> mock_data()
{
    vector<pair<double, double>> k = { make_pair<double, double>(3, 4),
                                       make_pair<double, double>(4, 7),
                                       make_pair<double, double>(12, 10),
                                       make_pair<double, double>(15, 6) };
    double x_scale = 12.0;
    double pos_x = 3.0;
    double pos_y = 4.0;
    for (size_t i = 0; i < k.size(); i++) {
        k[i].first = (k[i].first - pos_x) / x_scale;
        k[i].second = (k[i].second - pos_y) / x_scale;
    }
    return k;
}

int cal_gpu()
{
    return 0;
}

int factorial(int n)
{
    if (n == 0)
        return 1;
    int ret = n;
    for (int i = 1; i < n; i++) {
        ret *= i;
    }
    return ret;
}

int cal_cpu(vector<pair<double, double>> &data)
{
    int N = data.size() - 1;
    //   cout << "N is " << N << endl;
    vector<pair<double, double>> result(NUMS + 1);
    vector<int> C(N + 1);
    for (int i = 0; i < N + 1; i++) {
        C[i] = factorial(N) / (factorial(i) * factorial(N - i));
    }
    for (int idx = 0; idx <= 10; idx++) {
        double t = double(idx) / double(NUMS);
        result[idx].first = 0;
        result[idx].second = 0;
        for (int i = 0; i < N + 1; i++) {
            double Bin = C[i] * pow(t, i) * pow(1.0 - t, N - i);
            //   cout << "Bin is " << Bin << endl;
            result[idx].first += data[i].first * Bin;
            result[idx].second += data[i].second * Bin;
        }
    }

    //   for (size_t i = 0; i < 10; i++) {
    //     auto key = result[i];
    //     cout << key.first << ", " << key.second << endl;
    //   }
    return 0;
}

void print_every_second(bool &exit, mutex &mtx)
{
    while (true) {
        mtx.lock();
        if (exit == true) {
            return ;
        }
        mtx.unlock();

        this_thread::sleep_for(chrono::seconds(1));
        time_t now = time(nullptr);
        tm *now_t = localtime(&now);
        char now_str[64];
        strftime(now_str, sizeof(now_str), "%Y/%m/%d %H:%M:%S", now_t);
        cout << now_str << endl;
    }
}
int main()
{
    bool exit = false;
    mutex mtx;
    thread a(print_every_second, ref(exit), ref(mtx));
    int start = clock();
    auto data = mock_data();
    for (int i = 0; i < 100000; i++) {
        cal_cpu(data);
    }
    int end = clock();
    cout << "escape is " << double((end - start)) / double(CLOCKS_PER_SEC) << endl;
    mtx.lock();
    exit = true;
    mtx.unlock();
	a.join();
    return 0;
}