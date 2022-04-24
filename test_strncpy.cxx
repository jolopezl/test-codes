#include <cstring>
#include <iostream>
#include <string>

int main() {
    std::string source = "0123456789";
    char *dest = new char[source.size()];

    std::cout << "source = " << source << std::endl;
    std::cout << "dest = " << dest << std::endl;

    strncpy(dest, source.c_str(), source.size() + 1);

    std::cout << "dest = " << dest << std::endl;

    std::cout << "dest[size+1] = " << dest[source.size() + 1] << std::endl;
    std::cout << "source[size+1] = " << source[source.size() + 1] << std::endl;
    return 0;
}