#include <iostream>
#include <array>
#include <vector>
#include <chrono>

/*

   Compile it using some optimizations

   g++ -std=c++17 -O2 test_array_vector.cxx
 
   You would never produce the final code without minimum compiler optimization flags

*/

int main()
{
    constexpr long int kBIG = 1e6;

    // test an array
    // comment: this will fail at runtime with sufficiently large kBIG
    std::array<int, kBIG> xArr{};
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < kBIG; ++i) {
        xArr.at(i) += 1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total = end - start;
    std::cout << "It took " << total.count() << " seconds." << std::endl;
    std::cout << "Processed events using a array type" << std::endl;

    // test a vector
    std::vector<int> xVec(kBIG);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < kBIG; ++i) {
        xVec.at(i) += 1;
    }
    end = std::chrono::high_resolution_clock::now();
    total = end - start;
    std::cout << "It took " << total.count() << " seconds." << std::endl;
    std::cout << "Processed events using a vector type" << std::endl;

    return 0;
}
