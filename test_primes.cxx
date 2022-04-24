#include <stdio.h>

int is_prime(int n) {
    for (int i=2; i<=n/2; i++) 
        if (!(n%i))
            return 0;
    return 1;
}

int main() {
    int nn=0;
    for (int i=0; i<250001; i++)
        nn += is_prime(i);
    printf("%d\n", nn);
}

