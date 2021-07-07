#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

std::string input = "ABCDEFGHIJKLMNIOPRSTUVWXYZ";
std::string check = "ABCDEFGHIJKLMNIOPRSTUVWXYZ";

int f1()
{
    if (input == check)
        return -1;
    else
        return 0;
}

int f2()
{
    std::string_view x = input;
    if (x == check)
        return -1;
    else
        return 0;
}

int main()
{
    auto benchmark = [](auto fun, auto rem) {
        const auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 100000; ++i)
            fun();

        const std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
        //std::cout << "Time: " << std::fixed << std::setprecision(6) << diff.count()
        //          << " sec " << rem << std::endl;
        return diff.count();
    };

    for (int i = 0; i < 1e5; ++i) {
        auto t1 = benchmark(f1, "without optimizations");
        auto t2 = benchmark(f2, "with optimizations");
        std::cout << t1 << "," << t2 << std::endl;
    }
    return 0;
}
