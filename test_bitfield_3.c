#include <stdlib.h>
#include <stdio.h>

int main()
{
    struct T1 {
        union {
            uint64_t word;
            struct {
                uint16_t c : 16;
                uint16_t d : 16;
                uint16_t a : 8;
                uint16_t b : 8;
                uint16_t e : 16;
            };
        };
    };

    printf("Size of T1: %lu \n", sizeof(struct T1));
    struct T1 obj;
    printf("Size of T1 obj: %lu \n", sizeof(obj));

    // set the message values
    obj.a = 1;
    obj.b = 2;
    obj.c = 3;
    obj.d = 4000;
    obj.e = 50000;

    printf("message composition:\n");
    printf("   a: %d \n", obj.a);
    printf("   b: %d \n", obj.b);
    printf("   c: %d \n", obj.c);
    printf("   d: %d \n", obj.d);
    printf("   e: %d \n", obj.e);
    printf("message to be sent - word: %llu \n", obj.word);

    printf("\n");
    printf("Read the message bit-wise:\n");
    printf("obj.word >> 0  : %llu \n", obj.word >> 0 & 0xFF);
    printf("obj.word >> 8  : %llu \n", obj.word >> 8 & 0xFF);
    printf("obj.word >> 16 : %llu \n", obj.word >> 16 & 0xFFF);
    printf("obj.word >> 32 : %llu \n", obj.word >> 32 & 0xFFF);
    printf("obj.word >> 56 : %llu \n", obj.word >> 48 & 0xFFF);

    struct T1 obj_read;
    obj_read.word = obj.word;
    printf("message to recieved:\n");
    printf("word: %llu \n", obj_read.word);
    printf("message composition:\n");
    printf("   a: %d \n", obj_read.a);
    printf("   b: %d \n", obj_read.b);
    printf("   c: %d \n", obj_read.c);
    printf("   d: %d \n", obj_read.d);
    printf("   e: %d \n", obj_read.e);
}