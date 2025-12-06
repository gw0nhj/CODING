#include <stdio.h>

void main(int argc, char **argv) {
    int i;
    printf("받은 인자의 개수 : %d\n", argc);

    for(i = 0; i < argc; i++) {
        printf("이 프로그램이 받은 인자 : %s\n", argv[i]);
    }
}