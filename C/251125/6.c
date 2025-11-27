#include <stdio.h>

int main() {
    int num = 0;
    int N = 2000;
    printf("N = %d\n", (int)(N/3));
    unsigned int a, b, c;
    for(int a=(int)(N/3)+1; a<=N-2; a++) {

        for(int b=2; b<=N-a; b++) {

            c = N - a - b;
            if(c == 0) {
                continue;
            }

            if(a+b+c == N && a > b && b > c) {
                num++;
            }

        }

    }

    printf("Total combinations: %d\n", num);
    return 0;
}