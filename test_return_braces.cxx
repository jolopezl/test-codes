#include <iostream>

struct Foo {
    int i;
};

struct Bar {
    float f = 0;
    int i = 0;
};

Foo foo() {
// Bar foo() { // triggers a problem
    return {1};
}

int main() {
    std::cout << "foo().i = \t" << foo().i << std::endl;
    return 0;
}