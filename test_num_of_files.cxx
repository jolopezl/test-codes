//https://godbolt.org/z/sb4hY4Efz

#include <chrono>
#include <iostream>
#include <filesystem>
#include <string>

std::size_t f1(const std::string& path) {
    try {
        std::size_t counter = 0;
        auto it = std::filesystem::directory_iterator(path);
        for (const auto &f : it) {
            counter++;
        }
        return counter;
    } catch (std::filesystem::filesystem_error) {
        return -1;
    }
    return 0;
}

std::size_t f2(const std::string& path)
{
    std::size_t dst;
    try {
        dst = std::distance(std::filesystem::directory_iterator(path), std::filesystem::directory_iterator{});
    } catch (std::filesystem::filesystem_error) {
        dst = -1; // bug
    }
    return dst;
}

int main(int argc, char *argv[]) {
    const int N=1000;
    std::size_t nfiles1, nfiles2;
    const std::string path(argv[1]);

    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        nfiles1 = f1(path);
    }
    auto stop1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = stop1 - start1;
    std::cout << "elapsed time per call (1): " << elapsed_seconds1.count() / N << "s\n";

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        nfiles2 = f2(path);
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = stop2 - start2;
    std::cout << "elapsed time per call (2): " << elapsed_seconds2.count() / N << "s\n";


    std::cout << "nfiles1: " << nfiles1 << std::endl;
    std::cout << "nfiles2: " << nfiles2 << std::endl;

    return 0;
}
