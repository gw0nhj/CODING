#include <stdio.h>
#include <math.h>
#include <unistd.h>

int main() {
    size_t N = 16;
    scanf("%d", &N);
    size_t N2 = N;
    int calculate = 0;

    size_t arr[99] = {0, };

    int k = 0;

    // 소인수분해, N이 1이 될 때까지 계속해서 소인수로 나눔

    while(N != 1) {
        for(size_t i=2; i<=N; i++) {
            
            calculate++;

            if(i > sqrt(N2)) {
                arr[k] = N;
                k++;
                N = 1;
                break;
            }

            while(N % i == 0) {
                arr[k] = i;
                k++;
                N = N / i;
                calculate++;
            }

            if(i > 2) {
                i++;
            }

        }
    }
    
    for(int i=0; i<k; i++) {
        printf("Factor %d: %d\n", i+1, arr[i]);
    }

    printf("N: %d == ", N2);

    for(int i=0; i<k; i++) {
        printf("%d", arr[i]);
        if(i == k-1) {
            break;
        }
        printf(" * ");
    }

    printf("\nCalculatuion count: %d\n", calculate);

    return 0;
}
