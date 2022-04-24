#include <iostream>
#include <stdint.h>
#include <vector>

#define MASK(x) (1 << (x))

struct header
{
    union {
        uint32_t value;
        struct {
            uint32_t len : 16;
            uint32_t type : 16;
        };
    };
};


struct parser {
    std::vector<uint32_t> data;

    parser(std::vector<uint32_t> data) : data(data) {
        std::cout << "parser started (" << this << ")" << std::endl;
    }
    
    bool check() {
        header h = {.value = data[0]};
        if (data.size() != h.len) {
            return false;
        }
        return true;
    }
    
    void show_header() {
        header h = {.value = data[0]};
        std::cout << "header info:" << std::endl;
        std::cout << "value " << h.value << std::endl;
        std::cout << "len " << h.len << std::endl;
        std::cout << "type " << h.type << std::endl;
    }

    void payload() {
        if (!check()) {
            std::cout << "check failed" << std::endl;
            return;
        }
        for (int i = 1; i < data.size(); i++) {
            std::cout << data[i];
            std::cout << ", ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<uint32_t> data(10);
    header h;
    h.len = (uint16_t) 10;
    h.type = (uint16_t) 777;
    data[0] = h.value;

    parser p(data);
    p.check();
    p.show_header();
    p.payload();

    std::vector<uint32_t> data1(101);
    header h1;
    h1.len = (uint16_t) 99;
    h1.type = (uint16_t) 777;
    data1[0] = h1.value;

    parser p1(data1);
    p1.check();
    p1.show_header();
    p1.payload();

    return 0;
}