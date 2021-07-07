#include <chrono>
#include <iostream>
#include <vector>
#include <omp.h>

#define VECTOR_SIZE 1024 * 1024 * 1024

int f1()
{
    std::vector<unsigned int> vec(VECTOR_SIZE);
    vec[1024] = 1;
    vec[1035] = 1;
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        if (vec[i]) {
            vec[i] = 0;
        } else {
            vec[i] = -1;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = stop - start;
    std::cout << "Duration (usual)    = " << elapsed.count() << std::endl;
    return 0;
}

int f2()
{
    std::vector<unsigned int> vec(VECTOR_SIZE);
    vec[1024] = 1;
    vec[1035] = 1;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        if (vec[i] == 0) [[likely]] {
            vec[i] = 1;
        } else {
            vec[i] = 0;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = stop - start;
    std::cout << "Duration (builtint) = " << elapsed.count() << std::endl;
    return 0;
}

int main()
{
    f1();
    f2();
    return 0;
}
