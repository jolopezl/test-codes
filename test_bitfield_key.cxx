#include <stdlib.h>
#include <stdio.h>

int main()
{
    struct T1 {
        union {
            uint32_t word;
            struct {
                unsigned int det : 12;
                unsigned int pad : 8;
                unsigned int row : 8;
            };
        };
    };

    printf("Size of T1: %lu \n", sizeof(struct T1));
    struct T1 obj;
    printf("Size of T1 obj: %lu \n", sizeof(obj));

    // set the message values
    obj.det = 539; // 0-539
    obj.pad = 143; // 0-143
    obj.row = 15;  // 0-15

    printf("message composition:\n");
    printf("   det: %d \n", obj.det);
    printf("   pad: %d \n", obj.pad);
    printf("   row: %d \n", obj.row);
    printf("message to be sent - word: %u \n", obj.word);

    printf("\n");
    printf("Read the message bit-wise:\n");
    printf("obj.word (det) : %u \n", (obj.word & 0x00000FFF) >> 0);
    printf("obj.word (pad) : %u \n", (obj.word & 0x000FF000) >> 12);
    printf("obj.word (row) : %u \n", (obj.word & 0x0FF00000) >> 20);

    struct T1 obj_read;
    obj_read.word = obj.word;
    printf("message to recieved:\n");
    printf("word: %u \n", obj_read.word);
    printf("message composition:\n");
    printf("   det: %d \n", obj.det);
    printf("   pad: %d \n", obj.pad);
    printf("   row: %d \n", obj.row);

    return 0;
}
