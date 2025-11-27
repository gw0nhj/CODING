//씹어먹는 C언어 227p 4번
#include <stdio.h>
#include <math.h>

int CountPrime(int N) {

    if(N < 2) {
        printf("성립할 수 없음.\n");
        return 0;
    }

    int Count = 0;
    int Prime[12345];

    Prime[0] = 2;

    for(int i = 2; i <= N; i++) {

        for(int j = 0; j <= Count; j++) {

            if(i % Prime[j] == 0) {
                break;
            }

            if(j == Count) {
                Count++;
                Prime[Count] = i;
            }

        }

    }

    return ++Count;
}


void main() {
    int N = 0;

    printf("N보다 작은 소수의 개수를 세고자 한다.\n");
    printf("N = ");
    scanf("%d", &N);

    printf("%d",CountPrime(N));
}
