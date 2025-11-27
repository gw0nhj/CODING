//소수 찾기(N개)

#include <stdio.h>

int main(void) {
    int count = 0;
    int N = 2026;
    int prime[N];
    prime[0] = 2;
    int num = 2;

    while(count < N) {
        
        for(int i = 0; i <= count; i++) {
            if(num == 2) {
                printf("%5d", num);
                prime[++count] = num;
                num++;
                break;
            }
            if(num % prime[i] == 0) {
                num++;
                break;
            }
            if(num % prime[i] != 0 && i == count) {
                printf("%7d", num);
                prime[++count] = num;
                num++;
                break;
            }
        }
        
    }

    printf("\n총 소수의 개수: %d\n", count);
    return 0;
}