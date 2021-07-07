#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <omp.h>

const unsigned int N = 1024 * 1024 * 1024;

int main()
{
    std::vector<int> A(N, 0);
    std::vector<int> B(N, 0);

    auto start0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        A[i] = A[i] + B[i];
    }
    auto stop0 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds0 = stop0 - start0;
    std::cout << "(baseline)              elapsed time: " << elapsed_seconds0.count() << "s\n";

    auto start1 = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        A[i] = A[i] + B[i];
    }
    auto stop1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = stop1 - start1;
    std::cout << "(omp parallel for)      elapsed time: " << elapsed_seconds1.count() << "s\n";

    auto start2 = std::chrono::high_resolution_clock::now();
#pragma omp simd
    for (int i = 0; i < N; i++) {
        A[i] = A[i] + B[i];
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = stop2 - start2;
    std::cout << "(omp simd)              elapsed time: " << elapsed_seconds2.count() << "s\n";

    // auto start3 = std::chrono::high_resolution_clock::now();
    // for (int i=0; i<N/8; i++) {
    //     VECTOR_ADD(A + i, A + i, B + i);
    // }
    // auto stop3 = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed_seconds3 = stop3 - start3;
    // std::cout << "(simd)                  elapsed time: " << elapsed_seconds3.count() << "s\n";
}

// #pragma omp parallel for simd schedule (static,16)