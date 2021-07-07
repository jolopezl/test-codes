#include <array>
#include <iostream>

int main()
{
    //
    // Test array declaration in C++17
    //
    constexpr std::array<std::array<int, 2>, 3> arr = { { { 0, 1 }, { 2, 3 }, { 4, 5 } } };
    std::cout << arr.size() << std::endl;
    std::cout << arr[0].size() << std::endl;
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr[0].size(); j++) {
            std::cout << arr[i][j] << std::endl;
        }
    }
    return 0;
}