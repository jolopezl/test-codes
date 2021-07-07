#include "iostream"

class ToolClass
{
   public:
    ToolClass() { init(); }
    ~ToolClass() = default;
    void print() { std::cout << status << std::endl; }

   private:
    void init()
    {
        status = 1;
    }
    int status = 0;
};

class UserClass
{
   public:
    UserClass() = default;
    ~UserClass() = default;
    void init()
    {
        std::cout << "Init called" << std::endl;
    }
    ToolClass fExt;
};

int main()
{
    UserClass x;
    x.init();
    x.fExt.print();
}
