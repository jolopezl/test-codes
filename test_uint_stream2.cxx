#include <_types/_uint32_t.h>
#include <_types/_uint8_t.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdint>

template <typename T>
void Print(const T* data, size_t size, size_t width)
{
    for (size_t i = 0; i < size; ++i) {
        // std::cout << std::hex << std::setw(width) << std::setfill('0') << (int)data[i] << " ";
        std::cout << std::hex << std::setw(width) << std::setfill('0') << (int)data[i] << " ";
    }
    std::cout << std::endl;
};

void Print8(const uint8_t* data, size_t size)
{
    Print<uint8_t>(data, size, 2);
};

void Print32(const uint32_t* data, size_t size)
{
    Print<uint32_t>(data, size, 8);
};

int main()
{
    size_t N = 4; // the number of words to read
    uint32_t* data = new uint32_t[N];
    uint8_t* msg = new uint8_t[N * 4];
    uint32_t k = 0;

    for (uint32_t i = 0; i < N; i++) {
        msg[k++] = (data[i] >> 0) & 0xFF;
        msg[k++] = (data[i] >> 8) & 0xFF;
        msg[k++] = (data[i] >> 16) & 0xFF;
        msg[k++] = (data[i] >> 24) & 0xFF;
    }

    std::printf("----------------\n");
    Print8(msg, N * 4);
    Print32(data, N);
    std::printf("----------------\n");

    msg[4] = 0xF0;
    msg[5] = 0xFF;
    msg[6] = 0xFB;
    msg[7] = 0xFF;

    k = 0;
    for (uint32_t i = 0; i < N; i++) {
        // data[i] = (msg[i * 4 + 0] << 0) | (msg[i * 4 + 1] << 8) | (msg[i * 4 + 2] << 16) | (msg[i * 4 + 3] << 24);
        data[i] = msg[k] + msg[k + 1] * 0x100 + msg[k + 2] * 0x10000 + msg[k + 3] * 0x1000000;
        k += 4;
    }

    std::printf("----------------\n");
    Print8(msg, N * 4);
    Print32(data, N);
    std::printf("----------------\n");
}