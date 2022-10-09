#ifndef __CHANNEL_HEADER__
#define __CHANNEL_HEADER__
#include <mutex>

// 写一个管道类

template <typename T> class Channel;
template <typename T> bool operator>>(Channel<T> &self, T &it);


template <typename T> Channel<T>& operator<<(Channel<T> &self, T &it); // sync input

template <typename T> class Channel
{
    public:
    Channel(int cap);
    ~Channel();
    size_t size();
    size_t cap();

    friend bool operator>> <T> (Channel<T> &self, T &it); // sync output
    friend Channel<T>& operator<< <T>(Channel<T> &self, T &it); // sync input

    private:
    std::mutex mut;
    T *data;
    T *start_iter;
    T *end_iter;
    size_t cap_;
    bool close_;

    private:
    int realloc();
};


#endif 