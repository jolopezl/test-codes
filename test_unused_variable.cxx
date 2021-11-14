#include <iostream>

int main() {
    double a __attribute__((unused)); // OK.

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
    int b; // OK.
    #pragma GCC diagnostic pop

    std::cout << 1.0 << std::endl;
    return 0;
}
