#include <algorithm>
#include <cctype>    // std::tolower
#include <chrono>
#include <execution>
#include <iostream>
#include <string>
#include <vector>

#include <strings.h> // strcasecmp

// bool iquals(const std::vector<std::string> &pa, const std::vector<std::string> &pb) {
//     auto first1 = pa.begin();
//     auto last1 = pa.end() - 1; // without the alias
//     auto first2 = pb.begin();
//     for (; first1 != last1; ++first1, ++first2) {
//         if (strcasecmp((*first1).c_str(), (*first2).c_str()) != 0) {
//             return false;
//         }
//     }
//     return true;
// }
bool iquals(const std::vector<std::string> &pa, const std::vector<std::string> &pb) {
    if (pa.size() != pb.size()) {
        return false;
    }
    for (size_t i = 0; i < pa.size(); ++i) {
        if (strcasecmp(pa[i].c_str(), pb[i].c_str()) != 0) {
            return false;
        }
    }
    return true;
}

bool iequals_std(const std::vector<std::string> &pa, const std::vector<std::string> &pb) {
    if (pa.size() != pb.size()) {
        return false;
    }
    return std::equal(
        pa.begin(),
        pa.end(),
        pb.begin(),
        [](const std::string &a, const std::string &b) {
            return std::equal(
                a.begin(), a.end(),
                b.begin(), b.end(),
                [](const char &a, const char &b) {
                    return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
                });
        }
    );
}

void runTimeTest()
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

void runTest(const std::vector<std::string>& pa, const std::vector<std::string>& pb, const std::string& testName) {
    std::cout << "Running " << testName << ":" << std::endl;
    bool result1 = iquals(pa, pb);
    bool result2 = iequals_std(pa, pb);
    std::cout << " iquals result: " << (result1 ? "true" : "false") << std::endl;
    std::cout << " iequals_std result: " << (result2 ? "true" : "false") << std::endl;
    std::cout << " Test " << (result1 == result2 ? "PASSED" : "FAILED") << "\n" << std::endl;
}

int steerTest() {
    std::vector<std::string> testVector1 = {"Hello", "World", "Test", "Case", "Sensitive"};
    std::vector<std::string> testVector2 = {"hello", "world", "test", "case", "sensitive"};
    std::vector<std::string> testVector3 = {"Hello", "world", "Test", "Case", "Different"};
    std::vector<std::string> testVector4 = {"", "", "", "", ""};
    std::vector<std::string> testVector5 = {"", "B", "ccC", "D", "eeeeEEEE"};
    std::vector<std::string> testVector6 = {"a", "b", "ccc", "dddd", "eeeee"};
    std::vector<std::string> testVector7 = {"A", "B", "CcC", "DDdd", "EEEEEe"};

    // Test case 1: Identical strings with different cases
    runTest(testVector1, testVector2, "Test Case 1");

    // Test case 2: Same size, one element different
    runTest(testVector1, testVector3, "Test Case 2");

    // Test case 3: Vectors with empty strings
    runTest(testVector4, testVector4, "Test Case 3");

    // Test case 4: Mixed case with special characters
    runTest(testVector5, testVector6, "Test Case 4");

    // Test case 5: Same content, different cases and lengths
    runTest(testVector6, testVector7, "Test Case 5");

    // Test case 6: Different sizes
    std::vector<std::string> shortVector = {"Hello", "World"};
    runTest(testVector1, shortVector, "Test Case 6");

    // Test case 7: Empty vectors
    // std::vector<std::string> emptyVector;
    // runTest(emptyVector, emptyVector, "Test Case 7");

    return 0;
}

int main() {
    runTimeTest();
    return steerTest();
}