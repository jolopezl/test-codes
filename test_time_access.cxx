#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

const int N = 10000;

int main()
{
    struct Data {
        std::vector<float> data;
        std::vector<float> getData() const { return data; }
    };

    Data d;
    d.data.resize(N);
    std::for_each(d.data.begin(), d.data.end(), [](auto& v) { v = 1.0f; });

    std::vector<float> receiver(N);

    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N - 1; i++) {
        receiver[i] = d.getData()[i];
    }
    auto stop1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = stop1 - start1;
    std::cout << "elapsed time: " << elapsed_seconds1.count() << "s\n";

    auto start2 = std::chrono::high_resolution_clock::now();
    const auto& ref = d.getData();
    for (int i = 0; i < N - 1; i++) {
        receiver[i] = ref[i];
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = stop2 - start2;
    std::cout << "elapsed time: " << elapsed_seconds2.count() << "s\n";
}