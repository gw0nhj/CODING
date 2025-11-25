#include <stdio.h>

int main() {
    int N = 0;
    scanf("%d", &N);
    int result = 1;

    for(int i=1; i<=N; i++) {
        result *= i;
    }
    printf("Factorial of %d is %d\n", N, result);
    return 0;
}