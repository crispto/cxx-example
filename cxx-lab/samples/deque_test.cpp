#include <common.hpp>

int test1() {
    std::deque<int> que(3, 1);
    display_deque(que);
    for (int i = 0; i < 10; i++) {
        que.emplace_back(i * 10);
        display_deque(que);
    }
}
class Nexus {
  public:
    static int get_next() { return next_trackid++; }
    static int next_trackid;
};

int Nexus::next_trackid = 0;

class Tracker {
  public:
    Tracker();
    void show();
    int get_next() { return Nexus::get_next(); }

  private:
    float alpha = 0.5;
    char msg[20];
};

Tracker::Tracker(float _alpha, std::string v) : alpha(_alpha) {
    memcpy(msg, v.c_str(), v.size());
}
Tracker::show() {
    std::cout << "alpha: " << alpha << " msg " << msg << std::endl;
}

int uuid() {
    Tracker a;
    Tracker b;

    for (int i = 0; i < 10; i++) {
        std::cout << a.get_next() << std::endl;
        std::cout << b.get_next() << std::endl;
    }
}

int init_order() {
    Tracker v(12.5, "hello");
    v.show();
}
int main() { init_order(); }