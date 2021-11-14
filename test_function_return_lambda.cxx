#include <iostream>

auto heavy_side(int i, int j) {
    return [&] (int k) -> float {
        if (k < i) return 0.0f;
        else if (k > j) return 1.0f;
        else return 0.0f;
    };
}

int main() {
    auto hs = heavy_side(0, 10);
    std::cout << hs(-1) << std::endl;
    std::cout << hs(2) << std::endl;
    std::cout << hs(15) << std::endl;
    return 0;
}