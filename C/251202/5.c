#include <stdio.h>
#include <string.h>

void main(int argc, char **argv) {
    int i;
    printf("받은 인자의 개수 : %d\n", argc);

    int arr1, arr2;
    for(i = 0; i < argc; i++) {
        printf("섹\"%s\"스\n", argv[i]);
        // argv[i][0]은 문자(char)이므로 문자열 "+"이 아닌 문자 '+'와 비교해야 한다
        if(argv[i][0] == '+') printf("오호");
    }
}