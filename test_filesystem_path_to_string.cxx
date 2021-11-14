#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

int main() {
    std::filesystem::path image_root("/Users/lopez");

    std::vector<std::string> files1 = {{image_root / "fits" / "noise_3d.fits", image_root / "fits" / "noise_4d.fits"}};

    for (const auto &file : files1) {
        std::cout << file << std::endl;
    }

    std::vector<std::string> files2 = {(image_root / "fits" / "noise_3d.fits").string(), (image_root / "fits" / "noise_4d.fits").string()};

    for (const auto &file : files2) {
        std::cout << file << std::endl;
    }

    return 0;
}
