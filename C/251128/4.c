//311 Q2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void SmallToBig(char arr[]);

void main() {

    char String[101];
    scanf("%s", String);
    SmallToBig(String);

    printf("\n%s", String);
}

void SmallToBig(char arr[]) {

    int len = strlen(arr);
    short Num = 0;

    for(int i = 0; i < len; i++) {

        Num = (short)arr[i];

        if(64 < Num && Num < 91) {
            Num += 32;
        } // 대문자에서 소문자

        else if (96 < Num && Num < 123) {
            Num = Num - 32;
        } // 소문자에서 대문자

        arr[i] = Num;

    }
    
}