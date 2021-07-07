#include <iostream>

class bf
{
   public:
    bf() = default;
    ~bf() = default;

    void setX(int ix) { x = ix; }
    int getX() const { return x; }

   private:
    uint x : 10;
    uint y : 4;
    uint z : 8;
    uint u : 26;
};

struct BF1 {
    uint b : 1;
    uint a : 2;
};

int main()
{
    bf test;
    std::cout << sizeof(test) << std::endl;

    BF1 testBF1;
    std::cout << sizeof(uint) << std::endl;
    return 0;
}
