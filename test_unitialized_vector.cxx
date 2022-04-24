#include <vector>

struct uninitialized_int {
    int val;
    uninitialized_int() {;}
    operator int() const {return val;}
};

int main() {
    std::vector<uninitialized_int> vec;

    vec.resize(1024);
    vec[1] = 2;

    return vec[1];
}