#include <iostream>

using namespace std;

class Base
{
   public:
    Base() = default;
    ~Base() = default;
    void printName() { cout << "Name from Base " << mName << endl; }

   private:
    string mName{ "my name" };
};

class Spec : public Base
{
   public:
    Spec() = default;
    ~Spec() = default;
    void printName() { cout << "Name from Spec " << mName << endl; }

   private:
    string mName{ "my spec_name" };
    int mAge{ 10 };
};

int main()
{
    Base b;
    b.printName();
    Spec s;
    s.printName();
    return 0;
}