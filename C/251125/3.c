#include <stdio.h>
int main() {

    int N = 15;
    int SUM = 0;

    for (int i = 3; i <= N; i += 3) {
        SUM += i;
    }
    for (int i = 5; i <= N; i += 5) {
        SUM += i;
    }

    for (int i = 15; i <= N; i += 15) {
        SUM -= i;
    }

    printf("SUM : %d \n", SUM);

    return 0;
}