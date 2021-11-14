#include "iostream"
#include "array"

int main() {
    std::array<bool, 3> vec{};
    for (const auto &v : vec) std::cout << v << std::endl;
    vec[1] = true;
    for (const auto &v : vec) std::cout << v << std::endl;
    vec = {false};
    for (const auto &v : vec) std::cout << v << std::endl;
    return 0;
}
