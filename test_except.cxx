#include <iostream>
#include <exception>

#include <filesystem>
namespace fs = std::filesystem;

int f1()
{
    fs::path p = "/Users/lopez";
    std::cout << p.filename() << "\t" << fs::exists(p) << std::endl;

    // try {
    // auto it = fs::directory_iterator(p);
    // int counter = 0;
    // for (const auto d : it) {
    //     std::cout << d.path() << std::endl;
    //     counter++;
    // }

    // std::cout << counter << std::endl;

    auto it = fs::directory_iterator(p);
    // int counter = std::distance(it, fs::directory_iterator{});
    // std::cout << counter << std::endl;

    return (int)fs::exists(p);

    // } catch (fs::filesystem_error& e) {
    //     std::cout << e.what() << std::endl;
    // }

    return 0;
}

int compare(int a, int b)
{
    if (a == 0) {
        // throw std::runtime_error("a is 0");
        throw std::range_error("a is 0");
        // throw std::out_of_range("a is 0");
    } else {
        return a - b;
    }
}

int main()
{
    try {
        f1(); // should throw exception
        for (int i = -10; i < 10; i++) {
            std::cout << i << "\t" << compare(i, i + 1) << std::endl;
        }
    }
    catch (fs::filesystem_error& e) {
        std::cout << "[filesystem] -----> " << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cout << "[runtime_error] -----> " << e.what() << std::endl;
    }
}