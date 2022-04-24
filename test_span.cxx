#include <iostream>
#include <memory>
#include <span>
#include <vector>

int read_buffer(std::span<int> buffer) {
    return buffer.size();
}

void transform_buffer(std::span<int> buffer) {
    for (auto &i : buffer) {
        if (i == 0) {
            i = 1;
        }
    }
}

void print_buffer(const std::span<int> &buffer) {
    std::cout << "buffer: [ ";
    for (auto &i : buffer) {
        std::cout << i << " ";
    }
    std::cout << " ]" << std::endl;
}

int main() {
    int *buffer = new int[10];
    int values[10] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    for (int i = 0; i < 10; i++) {
        buffer[i] = values[i];
    }

    auto buffer_span = std::span<int>(buffer, 10);
    std::cout << "buffer size: " << read_buffer(buffer_span) << std::endl;
    print_buffer(buffer_span);
    transform_buffer(buffer_span);
    print_buffer(buffer_span);

    delete[] buffer;


    std::vector<int> vec = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    for (int i = 0; i < 10; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    auto vec_span = std::span<int>(vec);
    std::cout << "buffer size: " << read_buffer(vec_span) << std::endl;
    print_buffer(vec_span);
    transform_buffer(vec_span);
    print_buffer(vec_span);

    for (int i = 0; i < 10; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}