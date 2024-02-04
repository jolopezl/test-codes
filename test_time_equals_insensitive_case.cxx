#include <algorithm>
#include <cctype>    // std::tolower
#include <chrono>
#include <execution>
#include <iostream>
#include <string>
#include <vector>

#include <strings.h> // strcasecmp

bool iquals(const std::vector<std::string> &pa, const std::vector<std::string> &pb) {
    auto first1 = pa.begin();
    auto last1 = pa.end() - 1; // without the alias
    auto first2 = pb.begin();
    for (; first1 != last1; ++first1, ++first2) {
        if (strcasecmp((*first1).c_str(), (*first2).c_str()) != 0) {
            return false;
        }
    }
    return true;
}

bool iequals_std(const std::vector<std::string> &pa, const std::vector<std::string> &pb) {
    return pa.size() != pb.size() ? false : std::equal(
        pa.begin(),
        pa.end(),
        pb.begin(),
        pb.end(),
        [](const std::string &a, const std::string &b) {
            return std::equal(
                // std::execution::par_unseq,
                a.begin(),
                a.end(),
                b.begin(),
                [](const char &a, const char &b) {
                    return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
                });
        }
        );
}

int main()
{
    size_t N = 10000;

    std::vector<std::string> pa = {"a", "Bb", "CcC", "D", "AaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    std::vector<std::string> pb = {"A", "BB", "ccC", "d", "AaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    std::vector<std::string> pc = {"A", "BB", "ccC", "d", "AaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"};

    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        iquals(pa, pb);
    }
    auto stop1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = stop1 - start1;
    std::cout << "elapsed time (iquals)   : " << elapsed_seconds1.count() << "s\n";

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        iequals_std(pa, pb);
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = stop2 - start2;
    std::cout << "elapsed time (iquals_std): " << elapsed_seconds2.count() << "s\n";
}