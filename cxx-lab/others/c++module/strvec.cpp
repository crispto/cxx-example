#include <iostream>
#include <initializer_list>
using namespace std;
class Strvec
{
private:
        string *data, *finish, *end;
        static allocator<string> alloc;

        string *realloc(size_t n)
        {
                free();
                data = alloc.allocate(n);
                finish = data;
                end = data + n;
                return data;
        };
        void free()
        {
                for (string *pos = data; pos != finish; pos++) {
                        alloc.destroy(pos);
                }
                alloc.deallocate(data, end - data);
        };

public:
        Strvec() : data(nullptr), finish(nullptr), end(nullptr){};
        Strvec(initializer_list<string> li)
        {
                data = alloc.allocate(li.size());
                string *pos = data;
                for (auto k : li) {
                        alloc.construct(pos++, k);
                }
                end = pos;
                finish = pos;
        };
        Strvec(size_t n, const string &s = string())
        {
                data = alloc.allocate(n);
                string *pos = data;
                for (size_t i = 0; i < n; i++) {
                        alloc.construct(pos++, s);
                }
                end = pos;
                finish = pos;
        };
        Strvec(const Strvec &other)
        {
                data = alloc.allocate(other.size());
                string *pos = data;
                for (size_t i = 0; i < other.size(); i++) {
                        alloc.construct(pos++, other[i]);
                }
                end = pos;
                finish = pos;
        }
        Strvec(Strvec &&other) : data(other.data), finish(other.data), end(other.end)
        { // move constructor
                other.data = other.finish = other.end = nullptr;
        };
        Strvec &operator=(const Strvec &other)
        {
                if (size() < other.size()) {
                        realloc(other.size());
                }
                string *pos = data;
                for (size_t i = 0; i < other.size(); i++) {
                        alloc.construct(pos++, other[i]);
                }
                finish = pos;
                return *this;
        };
        Strvec &operator=(Strvec &&other)
        {
                data = other.data;
                finish = other.finish;
                end = other.end;
                other.data = other.finish = other.end = nullptr;
                return *this;
        }

        ~Strvec()
        {
                free();
        }
        string &operator[](size_t id) const
        {
                return data[id];
        };
        string &operator[](size_t id)
        {
                return data[id];
        };
        void push(const string &s)
        {
                if (end <= finish) {
                        // cout << "migrate .. " << endl;
                        size_t new_size = size() == 0 ? 1 : size() * 2;
                        string *new_data = alloc.allocate(new_size);
                        string *pos = new_data;
                        for (size_t i = 0; i < size(); i++) {
                                alloc.construct(pos++, std::move(data[i])); // 使用移动来构造函数
                                // alloc.construct(pos++, data[i]); // 使用copy来构造函数
                        }
                        free();
                        data = new_data;
                        finish = pos;
                        end = data + new_size;
                }
                alloc.construct(finish++, s);
        };
        string pop()
        {
                string v = std::move(*finish--);
                alloc.destroy(finish);
                return v;
        };
        bool empty() const
        {
                return finish == data;
        };

        size_t size() const
        {
                return finish - data;
        };
        size_t cap() const
        {
                return end - data;
        };
        Strvec get_val()
        {
                return *this;
        };
        Strvec &get_ref()
        {
                return *this;
        };
        Strvec sorted() &
        {
                cout << "lref only sorted" << endl;
                std::sort(data, finish);
                return *this;
        };
        Strvec sorted() const &&
        {
                cout << "rref only sorted" << endl;
                Strvec foo(*this);
                std::sort(foo.data, foo.finish);
                return foo;
        };
        void show()
        {
                for (size_t i = 0; i < size(); i++) {
                        cout << data[i] << " ";
                }
                cout << endl;
        }
};
allocator<string> Strvec::alloc;

int main()
{
        // Strvec v;
        // for (size_t i = 0; i < 5; i++) {
        //         v.push("hello");
        // }

        // for (size_t i = 0; i < v.size(); i++) {
        //         cout << v[i] << endl;
        // }

        // Strvec v2(std::move(v));
        // for (size_t i = 0; i < v2.size(); i++) {
        //         cout << v2[i] << endl;
        // }

        // for (size_t i = 0; i < v.size(); i++) {
        //         cout << v[i] << endl;
        // }
        // std::cout << "v is empty? " << v.empty() << endl;
        // for (size_t i = 0; i < v.size(); i++) {
        //         cout << v[i] << endl;
        // }
        Strvec v{ "f", "c", "b", "e" };
        Strvec v2 = v.get_val().sorted();
        v.show();
        cout << "---------------" << endl;
        v2.show();
        v.sorted();
        v.show();

        return 0;
}