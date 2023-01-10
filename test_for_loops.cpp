#include <stddef.h>
#include <stdio.h>

size_t nb = 0;

int f1() {
    size_t i;
    for (i=0; 4*i<nb; i++) {
        //
    }
    return i;
}

int f2() {
    size_t i;
    for (i=0; i<nb; i=i+4) {
        //
    }
    return i/4;
}

int main() {
    for (nb=4; nb<4096; nb++) {
        int check=nb/4;
        if (nb%4) check+=1;
        int if1 = f1();
        int if2 = f2();
        printf("%d\t%d\t%d\t%d", nb, check, if1, if2);
        if (check != if1 || check != if2) {
            printf("    ***** Error... nb = %d\n", nb);
            return 1;
        } else {
            printf("\n");
        }
    }
    return 0;
}