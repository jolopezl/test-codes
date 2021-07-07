#include <stdlib.h>
#include <stdio.h>

#pragma pack(1)

int main()
{
    struct T1 {
        union {
            uint64_t word;
            struct {
                uint16_t a : 16;
                uint16_t b : 8;
                uint16_t c : 16;
                uint16_t e : 16;
                uint16_t d : 8;
            };
        };
    };

    struct T2 {
        union {
            uint64_t word;
            struct {
                uint32_t a : 8;
                uint32_t b : 16;
                uint32_t c : 8;
                uint32_t d : 16;
                uint32_t e : 8;
                uint32_t f : 8;
            };
        };
    };

    printf("Size of T1: %lu \n", sizeof(T1));
    printf("Size of T2: %lu \n", sizeof(T2));
}
