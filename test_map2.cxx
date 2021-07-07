#include <map>
#include <iostream>

struct A {
    int a;
    std::map<int, int*> ma{ { 0, &a } };
};

int main()
{
    A sA;
    std::cout << sA.a << std::endl;
    *sA.ma[0] = -1;
    std::cout << sA.a << std::endl;
}