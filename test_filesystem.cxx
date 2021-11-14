#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
    fs::path p = "/Users/lopez";
    std::cout << p.filename() << "\t" << fs::exists(p) << std::endl;

    try {
        auto it = fs::directory_iterator(p);
        int counter = 0;
        for (const auto d : it) {
            std::cout << d.path() << std::endl;
            counter++;
        }

        std::cout << counter << std::endl;

        it = fs::directory_iterator(p);
        counter = std::distance(it, fs::directory_iterator{});
        std::cout << counter << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}