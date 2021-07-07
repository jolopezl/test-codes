#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>

int main()
{
    std::vector<int> vec1(1024 * 1024 * 1024);
    std::vector<int> vec2(vec1.size());

    //   for (int i = 0; i < vec1.size(); ++i) {
    //     std::cout << vec1[i] << "\t" << vec2[i] << std::endl;
    //   }

    auto t1 = std::chrono::high_resolution_clock::now();
    std::transform(std::execution::seq, vec1.begin(), vec1.end(), vec2.begin(), [](int& x) { return x + 1; });
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << ms.count() << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    std::transform(std::execution::par, vec1.begin(), vec1.end(), vec2.begin(), [](int& x) { return x + 1; });
    t2 = std::chrono::high_resolution_clock::now();
    ms = t2 - t1;
    std::cout << ms.count() << std::endl;

    return 0;
}