#include "channel.hpp"
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
template <typename T> Channel<T>::Channel(int cap) : close_(false), full_(false), cap_(cap)
{
    std::cout << "channel is start " << std::endl;
    data = new T[cap];
    start_iter = data;
    end_iter = data;
}
template <typename T> Channel<T>::~Channel()
{
    std::cout << "channel is terminal " << std::endl;
    delete[] data;
    end_iter = start_iter;
    close_ = true;
}

// 同步阻塞式读取
template <typename T> bool operator>>(Channel<T> &self, T &it)
{
    // std::cout << "read from channel " << std::endl;

    while (true) {
        // 这里要等到有数据为止?
        {
            std::lock_guard<std::mutex> lock(self.mut);
            if (self.start_iter != self.end_iter || self.full_) {
                it = *(self.start_iter);
                self.start_iter++;
                // move to the right pos
                if (self.start_iter == self.data + self.cap_)
                    self.start_iter = self.data;
                if (self.full_)
                    self.full_ = false;

                break;
            }
            // lock will unlock here
        }
        // check if closed
        if (self.close_)
            return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    // 没数据？
    return false;
}

// 同步阻塞写入
template <typename T> Channel<T> &operator<<(Channel<T> &self, T &in)
{
    // std::cout << "writing to channel " << std::endl;
    while (true) {
        {
            std::lock_guard<std::mutex> lock(self.mut);
            if (self.close_) {
                std::cout << "writing to closed channel" << std::endl;
                throw "writing to a closed channel";
            }
            if (!self.full_) {
                *(self.end_iter) = in;
                self.end_iter++;
                // move to the right pos
                if (self.end_iter - self.data == self.cap_)
                    self.end_iter = self.data;
                if (self.end_iter == self.start_iter)
                    self.full_ = true;

                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

template <typename T> size_t Channel<T>::size()
{
    std::lock_guard<std::mutex> lock(mut);
    if (full_)
        return cap_;

    size_t count = 0;
    T *p = start_iter;
    T *q = end_iter;
    while (p != q) {
        p++;
        count++;
        if (p == data + cap_)
            p = data;
    }
    return count;
}

template <typename T> size_t Channel<T>::cap()
{
    return cap_;
}

template <typename T> int Channel<T>::close()
{
    std::lock_guard<std::mutex> lock(mut);
    close_ = true;
}
void produce_thread(Channel<int> &ch, int id, int target_num, std::vector<bool> &end_list,
                    std::mutex &end_list_lock)
{
    for (int i = 0; i < target_num; i++) {
        int tmp = i;
        ch << tmp;
    }
    end_list_lock.lock();
    end_list[id] = true;
    bool closed = true;
    for (auto k : end_list) {
        if (!k) {
            closed = false;
            break;
        }
    }
    end_list_lock.unlock();
    if (closed)
        ch.close();
}

void consumer_thread(Channel<int> &ch, std::vector<int> &q)
{
    while (true) {
        int p;
        if (ch >> p)
            break;
        q.emplace_back(p);
    }
}

int main()
{
    // bool exit = false;
    // std::mutex exit_mut;
    const int produce_num = 8;
    const int consumer_num = 8;
    const int ch_size = 1000;
    const int target_num = 1000;

    std::vector<bool> end_list(produce_num, false);
    std::mutex end_list_mut;

    Channel<int> ch(ch_size);
    std::thread threads_vec[produce_num + consumer_num];
    for (size_t i = 0; i < produce_num; i++) {
        threads_vec[i] =
            std::thread(produce_thread, std::ref(ch), int(i), target_num, std::ref(end_list), std::ref(end_list_mut));
    }
    std::vector<int> ret[consumer_num];
    for (size_t i = 0; i < consumer_num; i++) {
        threads_vec[i + produce_num] =
            std::thread(consumer_thread, std::ref(ch), std::ref(ret[i]));
    }

    for (size_t i = 0; i < produce_num + consumer_num; i++) {
        threads_vec[i].join();
    }
    // merge three vectors
    std::vector<int> final_ret;
    for (size_t i = 0; i < consumer_num; i++) {
        auto q = ret[i];
        for (size_t i = 0; i < q.size(); i++) {
            final_ret.emplace_back(q[i]);
        }
    }
    std::sort(final_ret.begin(), final_ret.end());
    for (size_t i = 0; i < final_ret.size(); i++) {
        std::cout << final_ret[i] << ", ";
    }
    std::cout << std::endl;

    std::cout << "main over" << std::endl;
}