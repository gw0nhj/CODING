#include <stdio.h>

int main() {
    int Maximum = 1000000;
    int pibo[100];
    int Sum = 0;
    pibo[1] = 1;
    pibo[2] = 1;
    for(int i=3; pibo[i-1]<1000000; i++) {

        pibo[i] = (pibo[i-1] + pibo[i-2]);

    }

    for(int i=3; pibo[i]<1000000; i++) {

        if(pibo[i] % 2 == 0) {
            printf("odd pibo(%d) : %d\n", i, pibo[i]);
            Sum += pibo[i];
        }
    }
    printf("Sum : %d \n", Sum);
    return 0;
}