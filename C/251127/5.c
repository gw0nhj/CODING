//255p 2번 문제
#include <stdio.h>

int GCD(int a, int b);

void main() {
    int num1, num2;
    scanf("%d %d", &num1, &num2);

    printf("%d", GCD(num1, num2));

}

int GCD(int a, int b) {
    if(a == 0) return b;
    if(b == 0) return a;

    if(a >= b) { 
        a = a % b;
    }

    printf("%d, %d\n", a, b);
    GCD(b, a);
}