// test_bitset_set_map.cxx

#include <chrono>
#include <iostream>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <random> // for random numbers from the cpp stl
#include <numeric>

#define SIZE 1000 * 1000

int main()
{
    // std::vector<unsigned int> keys(1000);
    // std::iota (std::begin(keys), std::end(keys), 0);
    std::vector<unsigned int> indexes(SIZE);
    std::default_random_engine dre;
    std::uniform_int_distribution<unsigned int> rand(0, SIZE - 1);
    for (size_t i = 0; i < SIZE; ++i) {
        auto idx = rand(dre);
        indexes.push_back(idx);
    }

    // TEST 1
    std::bitset<SIZE> bitset_keys;
    auto start = std::chrono::high_resolution_clock::now();
    unsigned int counter = 0;
    for (const auto& idx : indexes) {
        if (!bitset_keys.test(idx)) {
            bitset_keys.set(idx);
        }
    }
    counter = bitset_keys.count();
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = stop - start;
    std::cout << "counts: " << counter << ", (bitset) elapsed time: " << elapsed_seconds.count() << "s\n";

    // TEST 2
    std::unordered_set<unsigned int> uset_keys;
    start = std::chrono::high_resolution_clock::now();
    counter = 0;
    for (const auto& idx : indexes) {
        if (!uset_keys.count(idx)) {
            uset_keys.insert(idx);
        }
    }
    counter = uset_keys.size();
    stop = std::chrono::high_resolution_clock::now();
    elapsed_seconds = stop - start;
    std::cout << "counts: " << counter << ", (unordered_set) elapsed time: " << elapsed_seconds.count() << "s\n";

    // TEST 3
    std::unordered_map<unsigned int, unsigned int> umap_keys;
    start = std::chrono::high_resolution_clock::now();
    counter = 0;
    for (const auto& idx : indexes) {
        if (!umap_keys.count(idx)) {
            umap_keys[idx] = 1;
        }
    }
    counter = uset_keys.size();
    stop = std::chrono::high_resolution_clock::now();
    elapsed_seconds = stop - start;
    std::cout << "counts: " << counter << ", (unordered_map) elapsed time: " << elapsed_seconds.count() << "s\n";

    std::cout << "size of (bitset use)" << sizeof(std::bitset<SIZE>) + SIZE * sizeof(int) << std::endl;
    std::cout << "size of (unsigned set use)" << sizeof(std::unordered_set<int>) + SIZE * sizeof(int) << std::endl;
    std::cout << "size of (unsigned map use)" << (sizeof(std::unordered_map<int, int>) + SIZE * sizeof(int)) * 2 << std::endl;

    return 0;
}