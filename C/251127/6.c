//255p Q3

#include <stdio.h>

size_t Multiplier(int N);

void main() {
    
    int N = 16;

    printf("%d", Multiplier(N));
}

size_t Multiplier(int N) {
    if(N == 1) return 1;

    return N * Multiplier(N - 1);
}