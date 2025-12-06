//memcpy 함수를 이용한 문자열 복사
#include <stdio.h>
#include <string.h>

void main () {
    char String1[30]= "Wow Do you know Sans?";
    char String2[30];
    memcpy(String2, String1, strlen(String1) + 1);

    printf("%s", String2);
}