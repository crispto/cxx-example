#include <iostream>
#include <set>
using namespace std;

class Message;
class Folder
{
private:
        set<Message *> msgs;

public:
        Folder() = default;

public:
        void saveMsg(Message *m)
        {
                msgs.insert(m);
        };
        void delMsg(Message *m)
        {
                msgs.erase(m);
        }

        void listMsg();
};

class Message
{
private:
        set<Folder *> folders_;
        string content_;
        void save_to_folders(const Message &input)
        {
                for (auto &f : input.folders_) {
                        f->saveMsg(this);
                }
        }
        void rm_from_folders()
        {
                for (auto &f : folders_) {
                        f->delMsg(this);
                }
        }

public:
        Message(const string &s = string()) : content_(s){};
        Message(const Message &other)
        {
                folders_ = other.folders_;
                save_to_folders(other);
        };
        Message &operator=(Message &other)
        {
                rm_from_folders();
                save_to_folders(other);
                folders_ = other.folders_;
                content_ = other.content_ + "_back";
                return *this;
        };
        ~Message()
        {
                rm_from_folders();
        }

        void save(Folder &f)
        {
                folders_.insert(&f);
                f.saveMsg(this);
        };
        void remove(Folder &f)
        {
                folders_.erase(&f);
                f.delMsg(this);
        };
        string getContent()
        {
                return content_;
        };
        void show(){
            cout << "content: " << content_ << endl;
        };
        friend void swap(Message &m1, Message &m2);
};

void swap(Message &m1, Message &m2)
{
        m1.rm_from_folders();
        m2.rm_from_folders();
        m1.save_to_folders(m2);
        m2.save_to_folders(m1);
        std::swap(m1.folders_, m2.folders_);
        std::swap(m1.content_, m2.content_);
};

void Folder::listMsg()
{
        cout << "----------------------" << endl;
        int count = 0;
        for (auto &m : msgs) {
                printf("[%d]: %s\n", count++, m->getContent().c_str());
        }
        cout << "----------------------" << endl;
}

int main()
{
        Folder a, b;
        Message m1("message1");
        m1.save(a);
        m1.save(b);

        Message m2("message2");
        m2.save(a);
        a.listMsg();
        b.listMsg();
        m1.show();
        m2.show();
        cout << "&&&&&&&&&&&&&&&&&&&&&&" << endl;
        swap(m1, m2);
        m1.show();
        m2.show();
        a.listMsg();
        b.listMsg(); 
}