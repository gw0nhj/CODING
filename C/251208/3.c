// AND 연산 이용
// p546

#include <stdio.h>

void main(){

    int Num = 123241;
    if(Num & 1) {
        printf("홀");
    }
    else {
        printf("짝");
    }

    return;
}