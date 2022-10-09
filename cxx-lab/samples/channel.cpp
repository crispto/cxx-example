#include "channel.hpp"
#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

template <typename T> Channel<T>::Channel(int cap) : close_(false), cap_(cap)
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

// read from a channel
template <typename T> bool operator>>(Channel<T> &self, T &it)
{
    std::cout << "operator >> is running " << std::endl;
    
    while(true){
        // 这里要等到有数据为止?
        {
            self.mut.lock();
                
            if (self.start_iter < self.end_iter) {
                it = *(self.start_iter);
                self.start_iter++;
                break;
            }

        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    // 没数据？
    return false;
}

template <typename T> size_t  Channel<T>::size()
{
    return end_iter - start_iter;
}

template <typename T> size_t Channel<T>::cap()
{
    return cap_;
}

int main()
{
    Channel<int> ch(size_t(20));
    int i = 0;
    ch >> i;
}