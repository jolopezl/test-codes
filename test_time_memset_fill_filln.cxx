#include <execution>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include <cstring>

const int N = 10000;

int main()
{
    std::vector<int> data(1024 * 1024 * 1024);
    const auto N = data.size();

    auto start1 = std::chrono::high_resolution_clock::now();
    std::for_each(data.begin(), data.end(), [](auto& x) { x = 0; });
    auto stop1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = stop1 - start1;

    auto start11 = std::chrono::high_resolution_clock::now();
    std::for_each(
      std::execution::par,
      std::begin(data),
      std::end(data),
      [](auto& x) { x = 0; });
    auto stop11 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds11 = stop11 - start11;

    auto start2 = std::chrono::high_resolution_clock::now();
    memset(&data[0], 0, sizeof(int) * N);
    auto stop2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = stop2 - start2;

    auto start3 = std::chrono::high_resolution_clock::now();
    std::fill(data.begin(), data.end(), 0);
    auto stop3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds3 = stop3 - start3;

    auto start4 = std::chrono::high_resolution_clock::now();
    std::fill_n(data.begin(), data.size(), 0);
    auto stop4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds4 = stop4 - start4;

    std::cout << "elapsed time (for_each)        : " << elapsed_seconds1.count() << "s\n";
    std::cout << "elapsed time (for_each par)    : " << elapsed_seconds11.count() << "s\n";
    std::cout << "elapsed time (memset)      : " << elapsed_seconds2.count() << "s\n";
    std::cout << "elapsed time (std::fill)   : " << elapsed_seconds3.count() << "s\n";
    std::cout << "elapsed time (std::fill_n) : " << elapsed_seconds4.count() << "s\n";
}