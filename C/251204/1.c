// memmove를 이용한 문자열 복사

#include <stdio.h>
#include <string.h>

void main() {
    char String[30] = "Wow, Do you know Sans?";

    memmove(String + 21, String + 17, 5);
    printf("%s", String);
}