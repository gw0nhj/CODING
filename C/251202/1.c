// 공용체
#include <stdio.h>

union A {
    int i;
    char j[4];
} AA;

void main() {
    AA. i = 0x12345678;
    printf("%x", AA. j[3]);
}