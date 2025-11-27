#include <stdio.h>

int main(void) {
    puts("실수를 입력하세요: ");
    float f;
    scanf("%f", &f);
    int i = (int)(f * 100) % 100;
    printf("소수점 아래 두 자리: %02d\n", i);
    return 0;
}