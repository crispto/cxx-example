#include <iostream>

class BaseDoc
{
    public:
    virtual void serial() = 0;
    virtual void prompt()
    {
        std::cout << "BaseDoc::prompt" << std::endl;
    };
    void on_open()
    {
        std::cout << "BaseDoc::on_open" << std::endl;
        prompt();
        serial();
    }
};

class WordDoc : public BaseDoc
{
    public:
    virtual void prompt() override
    {
        std::cout << "WordDoc::prompt" << std::endl;
    };
     void serial() final
    {
        std::cout << "WordDoc::serial" << std::endl;
    };
};

int main()
{
    WordDoc doc;
    doc.on_open();

    // 如果是一個非純虛函数呢 
    // 继承类中的virtual 代表它可以被选择性 override
}