/*
        https://stackoverflow.com/questions/29859796/c-auto-vs-auto/29860056#29860056
*/

#include <numeric>
#include <iostream>
#include <vector>

#define PRINT(X)                \
    for (const auto& v : X) {   \
        std::cout << v << "\t"; \
    }                           \
    std::cout << std::endl;

int main()
{
    std::vector<int> vec(10);
    std::iota(vec.begin(), vec.end(), 0);

    std::cout << "Initial vector" << std::endl;
    PRINT(vec);

    for (auto&& v : vec) {
        v = v + 1;
    }

    std::cout << "Result" << std::endl;
    for (const auto& v : vec) {
        std::cout << v << "\t";
    }

    std::cout << std::endl;
}
