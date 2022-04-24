#include <iostream>

int main() {
    const int x(-1), y(1);
    const int z = [&] {
        int zv;
        zv = x * y;
        return zv;
    }();
    std::cout << "z = " << z << std::endl;
    return 0;
}
